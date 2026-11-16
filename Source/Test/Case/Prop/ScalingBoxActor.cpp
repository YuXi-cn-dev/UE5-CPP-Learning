// Fill out your copyright notice in the Description page of Project Settings.


#include "ScalingBoxActor.h"
#include "Components/StaticMeshComponent.h" //调用静态网格体组件的头文件，必须要包含它

// Sets default values
AScalingBoxActor::AScalingBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 创建一个静态网格体组件，名字叫 BoxMesh
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));

    // 把 BoxMesh 设为根组件( 第二种配置根骨骼的代码: RootComponent = BoxMesh; )
	BoxMesh->SetupAttachment(RootComponent);

	//游戏开始先不进行缩放
	RunningTime = 0.0f;
	bIsScaling = false;
}

// Called when the game starts or when spawned
void AScalingBoxActor::BeginPlay()
{
	Super::BeginPlay();

	//游戏开始进行开始缩放大小
	InitialScale = GetActorScale3D(); //方块一开始的大小
	RunningTime = 0.0f; //时间从 0 开始算
	bIsScaling = true; //打开缩放开关
	
}

// Called every frame
void AScalingBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 如果缩放开关关掉了，就直接返回，不再执行下面的缩放代码(这样游戏结束后就能停止缩放)
	if (!bIsScaling)
	{
		return;
	}

    // 把每帧经过的时间累加起来(相当于一个不停增加的计时器)
	RunningTime += DeltaTime;

	// FMath::Sin(...) 会输出 -1 到 1 之间来回变化的值
	// 加 1 再乘 0.5，就变成 0 到 1 之间来回变化
	// 可以把它理解成“缩放变化的百分比”
	float ScaleFactor = ((FMath::Sin(ScaleSpeed * RunningTime) + 1.0f) * 0.5);

	// Lerp 的意思是“在两个数之间按比例取中间值”
	// 这里就是在 MinScaleRatio 和 MaxScaleRatio 之间平滑变化
	// 比如 0.5 到 1.5 之间来回变
	float CurrentScaleMultiplier = FMath::Lerp(MinScaleRatio, MaxScaleRatio, ScaleFactor);

	// 最终大小 = 一开始的大小 × 当前倍率
	FVector NewScale = InitialScale * CurrentScaleMultiplier;

	// 把算出来的新大小真正应用到 Actor 上(这样你在游戏里就能看到它变大变小)
	SetActorScale3D(NewScale);

	AddActorLocalRotation(FRotator(0.0f, -90.0f * DeltaTime, 0.0f));
}

// 游戏结束、Actor 被销毁、关卡切换时会自动调用
void AScalingBoxActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//先让父类做它该做的收尾工作
	Super::EndPlay(EndPlayReason);

	// 把缩放开关关掉
    // Tick 里看到 bIsScaling 是 false，就会直接 return
    // 于是方块就停止变大变小了
	bIsScaling = false;
}
