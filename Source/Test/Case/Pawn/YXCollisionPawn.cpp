// Fill out your copyright notice in the Description page of Project Settings.


#include "YXCollisionPawn.h"
#include "UObject/ConstructorHelpers.h" // 构造辅助：在构造函数里安全加载资源
#include "Particles/ParticleSystemComponent.h" // 粒子系统组件：Cascade 粒子特效
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Test/Component/YXPawnMovementComponent.h"


// Sets default values
AYXCollisionPawn::AYXCollisionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建球体组件
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));

	//设为根组件
	RootComponent = SphereComponent;

	//设置球的半径( InitSphereRadius -> 初始化球体半径（必须在构造函数里调用，所以叫 Init）)
	SphereComponent->InitSphereRadius(40.0f);

	//设置碰撞配置( SetCollisionProfileName -> 设置碰撞预设方案（Preset） )
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	//创建静态网格组件
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));

	//把球体挂到根组件下
	SphereVisual->SetupAttachment(RootComponent);

	//加载模型资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Mesh/Sphere.Sphere"));

	//判断模型是否加载成功（ Succeeded() 判断资源是否加载成功。）?
	if (SphereVisualAsset.Succeeded())
	{
		//给组件设置模型
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);

		//设置相对位置
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));

		//设置缩放
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// 创建粒子组件
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));

	//挂载到可视模型（SphereVisual）上
	OurParticleSystem->SetupAttachment(SphereVisual);

	//关闭自动激活
	OurParticleSystem->bAutoActivate = false;

	//设置前后相对位置
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));

	//加载粒子资源
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/InventoryKit/Environment/Particles/PS_LootFX.PS_LootFX"));

	//如果资源加载成功，把它塞给粒子组件
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//使用弹簧臂给予摄像机平滑自然的运动感
	USpringArmComponent* SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComp->TargetArmLength = 400.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	//把摄像机挂载到弹簧臂的插槽上 
	UCameraComponent* CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//创建自定义移动组件,并且对它更新根节点
	OurMovementComponent = CreateDefaultSubobject<UYXPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;


	//控制默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// 直接把你在头文件里声明的那个自定义移动组件返回出去
UPawnMovementComponent* AYXCollisionPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

// Called when the game starts or when spawned
void AYXCollisionPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AYXCollisionPawn::YXMoveForward(float AxisValue)
{
	// 只要移动组件存在，就往前走
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent = RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector()* AxisValue);
	}
}

void AYXCollisionPawn::YXMoveRight(float AxisValue)
{
	// 只要移动组件存在，就往右走
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent = RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void AYXCollisionPawn::Turn(float AxisValue)
{
	//控制左右转身
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void AYXCollisionPawn::ParticleToggle()
{
	// 确保粒子组件存在
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		//ToggleActive()->切换激活
		OurParticleSystem->ToggleActive();
	}
}

// Called every frame
void AYXCollisionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYXCollisionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// 绑定轴（Axis）输入 - 持续触发（每帧都调用）
		PlayerInputComponent->BindAxis("MoveForward", this, &AYXCollisionPawn::YXMoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AYXCollisionPawn::YXMoveRight);
		PlayerInputComponent->BindAxis("Turn", this, &AYXCollisionPawn::Turn);

		// 绑定动作（Action）输入 - 按一下触发一次
		// IE_Pressed ->按下
		// IE_Released ->松开
		PlayerInputComponent->BindAction("ParticleToggle", IE_Pressed, this, &AYXCollisionPawn::ParticleToggle);
	}

}

