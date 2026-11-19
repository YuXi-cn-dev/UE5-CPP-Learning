// Fill out your copyright notice in the Description page of Project Settings.


#include "YXFPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h" //添加胶囊体碰撞组件头文件

// Sets default values
AYXFPSCharacter::AYXFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建第一人称摄像机组件
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	//将摄像机组件附加到胶囊体组件上
	//写法二:
	//FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));// 获取角色的胶囊体组件，并安全地转换为场景组件(USceneComponent)类型传给函数

	// 设置摄像机相对于胶囊体的位置( BaseEyeHeight: 基础眼睛高度, 默认通常是 64.0f（厘米）。这个值原本是用来告诉 AI 或者物理系统，这个角色的“视线”有多高.)
	// SetRelativeLocation()  -> 设置相对位置
	FPSCameraComponent->SetRelativeLocation(FVector(26.0f, 0.0f, 10.0f + BaseEyeHeight));

	// 开启摄像机的“使用控制器旋转”功能
	FPSCameraComponent->bUsePawnControlRotation = true;

	//为所属玩家创建第一人称网格体组件
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	check(FPSMesh != nullptr);

	//获取第一人称专属网格体，将其设置为“仅拥有者可见”。
	FPSMesh->SetOnlyOwnerSee(true);

	//把FPS网格体附加FPS摄像机
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 关闭第一人称网格体的动态阴影投射
	// 防止靠近墙壁或地面时，出现穿帮的手部/武器黑影
	FPSMesh->bCastDynamicShadow = false;

	// 彻底关闭该组件的阴影投射总开关
	FPSMesh->CastShadow = false;

	// 获取角色的主全身模型，将其设置为“拥有者不可见”。
	GetMesh()->SetOwnerNoSee(false);
}

// Called when the game starts or when spawned
void AYXFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AYXFPSCharacter::MoveForward(float Value)
{
	// 获取控制器（摄像机）的朝向，计算出一个基于世界坐标的移动方向
	// GetScaledAxis(EAxis::X) -> 从矩阵中，把“X轴”的方向单独抽出来，赋值给 Direction
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	//写法二( 新手推荐 ):
	//Controller->GetControlRotation().Vector(); // 获取旋转对应的前方向量

	// 将计算好的方向和移动数值（Value）应用到角色身上
	AddMovementInput(Direction, Value);
}

void AYXFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}

void AYXFPSCharacter::StartJump()
{
	// bPressedJump -> 跳跃键是否被按下了
	bPressedJump = true;
}

void AYXFPSCharacter::StopJump()
{
	bPressedJump = false;
}

// Called every frame
void AYXFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYXFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定移动操作
	PlayerInputComponent->BindAxis("MoveForward", this, &AYXFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",   this, &AYXFPSCharacter::MoveRight);

	//绑定视角操作
	PlayerInputComponent->BindAxis("Turn",   this, &AYXFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AYXFPSCharacter::AddControllerPitchInput);

	//绑定跳跃操作
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AYXFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released,this, &AYXFPSCharacter::StopJump);
}

