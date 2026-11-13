// Fill out your copyright notice in the Description page of Project Settings.


#include "YXPawnWithCamera.h"
#include "GameFramework/SpringArmComponent.h"  // 引入弹簧臂组件头文件
#include "Camera/CameraComponent.h"           //  引入摄像机组件头文件
#include "Components/StaticMeshComponent.h"  //   引入静态网格体组件头文件

// 这是这个类的构造函数。每次在游戏里生成这个 Pawn，或者在编辑器里拖入场景时，都会执行一次。
AYXPawnWithCamera::AYXPawnWithCamera()
{
	// 让这个 Pawn 每一帧都执行 Tick 函数。如果你想节省性能且不需要它每帧更新，可以设为 false。
	PrimaryActorTick.bCanEverTick = true;

	// ----------------- 第一步创建组件 -----------------
	// CreateDefaultSubobject -> 在游戏还没开始运行（编辑器里）的时候，就“凭空造”出一个组件，并给它起个内部名字。

	// 1. 创建一个基础的场景组件作为“根节点”,名字叫:"RootComponent"。
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// 2. 创建静态网格体组件，名字叫:"MeshComponent"。
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// 3. 创建弹簧臂组件（负责摄像机拉伸和平滑）,名字叫:"SpringArm"。
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// 4. 创建摄像机组件,名字叫:"CameraComponent"。
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	// ----------------- 第二步绑定组件 -----------------
	// SetupAttachment() -> 设置附加/挂载”。
    // 1. 把模型挂载到根节点上 
	StaticMeshComp->SetupAttachment(RootComponent);

	// 2. 把弹簧臂挂载到静态网格体（模型）上
	SpringArmComp->SetupAttachment(StaticMeshComp);

	// 3. 把摄像机挂载到弹簧臂的插槽上 
	//USpringArmComponent::SocketName   -> 弹簧臂的插槽名称
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// ---------------- 第三步设置摇臂属性 -----------------
	//1. 调整镜头的位置和角度
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));

	//2. 设定弹簧臂的长度
	SpringArmComp->TargetArmLength = 400.0f;

	//3. 启用“摄像机延迟”
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	// ---------------- 第四步控制游戏角色 -----------------
	//游戏一开始，就自动让本地玩家0号（Player0）控制游戏角色.
	//1.AutoPossessPlayer：自动附身玩家。它是 APawn 类自带的一个属性。
    //2.EAutoReceiveInput：这是一个枚举（Enum），列出了可以被哪些玩家控制（Player0 代表第一个玩家，也就是键盘鼠标操作的那个；
	//                                                                                 如果有分屏，还有 Player1、Player2 等）。
    //3.Player0：指定 0 号玩家。
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AYXPawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYXPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ---------------- 第六步处理瞄准缩放 -----------------
	// 1. 判断是否按下了瞄准键
	if (bZoomIn)
	{
		// 如果按下了，ZoomFactor 增加。除以 0.5f 意味着“用 0.5 秒的时间完成拉近”
		ZoomFactor += DeltaTime / 0.5f;
	}
	else
	{
		// 如果没按（松开），ZoomFactor 减少。除以 0.25f 意味着“用 0.25 秒的时间恢复原状”
		ZoomFactor -= DeltaTime / 0.25f;
	}

	// 2. 限制范围，确保 ZoomFactor 只能在 0（不瞄准） 到 1（完全瞄准） 之间变化
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	// 3. 根据 ZoomFactor 的百分比，实时计算当前的视野（FOV）和弹簧臂长度

	// 【加这行】实时打印当前 ZoomFactor 的值
	GEngine->AddOnScreenDebugMessage(1, 0.01f, FColor::Green, FString::Printf(TEXT("当前 ZoomFactor: %f"), ZoomFactor));

	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	
	
	// ---------------- 第七步处理角色移动和视角旋转 -----------------
	//第一段：控制身体左右转身（Yaw）
	{
		//1. 获取角色现在的朝向
		FRotator NewRotation = GetActorRotation();

		// 2. 加上鼠标左右滑动的距离
		NewRotation.Yaw += CameraInput.X;

		//3. 设置角色新的朝向
		SetActorRotation(NewRotation);
	}

	//第二段：控制脖子抬头低头（Pitch）
	{
		// 1. 获取弹簧臂现在的角度
		FRotator NewRotation = SpringArmComp->GetComponentRotation();

		// 2. 加上鼠标上下滑动的距离，并且用 Clamp 锁死在 -80度 到 -15度 之间
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);

		// 3. 设置弹簧臂新的角度
		SpringArmComp->SetWorldRotation(NewRotation);
	}

	//第三段：控制双腿走路（Move）
	{
		// 1. 如果你按了键盘（输入不是0）
		if (!MovementInput.IsZero())
		{
			// 2. 把输入归一化（防止斜着走速度变快）
			FVector2D MoveDirection = MovementInput.GetSafeNormal();

			// 3. 获取角色现在的坐标
			FVector NewLocation = GetActorLocation();

			// 4. 计算新坐标：朝角色正前方走 X，朝角色右方走 Y。乘以100是速度，乘以DeltaTime是为了不受电脑卡顿影响
			NewLocation += GetActorForwardVector() * MoveDirection.X * 100.0f * DeltaTime;
			NewLocation += GetActorRightVector() * MoveDirection.Y * 100.0f * DeltaTime;

			// 5. 把角色移动到新坐标
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AYXPawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ---------------- 第五步创建按键函数和绑定按键事件 -----------------
	// 绑定移动
	InputComponent->BindAxis("MoveForward", this, &AYXPawnWithCamera::YXMoveForward);
	InputComponent->BindAxis("MoveRight",   this, &AYXPawnWithCamera::YXMoveRight);

	// 绑定视角
	InputComponent->BindAxis("CameraPitch", this, &AYXPawnWithCamera::YXPitchCamera);
	InputComponent->BindAxis("CameraYaw",   this, &AYXPawnWithCamera::YXYawCamera);

	// 绑定缩放 (注意这里是BindAction，因为是按下/松开)
	InputComponent->BindAction("ZoomIn",  IE_Pressed,  this, &AYXPawnWithCamera::YXZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Released, this, &AYXPawnWithCamera::YXZoomOut);

}

//1. 安全的移动输入
void AYXPawnWithCamera::YXMoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void AYXPawnWithCamera::YXMoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

//2. 记录鼠标的转动
void AYXPawnWithCamera::YXPitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AYXPawnWithCamera::YXYawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

//3. 瞄准（缩放）开关
void AYXPawnWithCamera::YXZoomIn()
{
	bZoomIn = true;

	// 【加这行】如果按下右键，屏幕左上角会弹红字
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("按键成功触发！ZoomIn 被调用了！"));
}

void AYXPawnWithCamera::YXZoomOut()
{
	bZoomIn = false;
}



