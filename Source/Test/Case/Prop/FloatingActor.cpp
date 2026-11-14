// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建静态网格体组件
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//设置静态网格体组件的父组件为根组件
	VisualMesh->SetupAttachment(RootComponent);

	//指定静态网格体资产
	// ------不推荐这种做法-----------
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Mesh/SM_ChamferCube.SM_ChamferCube"));

	//检查静态网格体资产是否加载成功
	//if (CubeVisualAsset.Succeeded())
	//{
		//设置静态网格体组件的静态网格体资产
		//VisualMesh->SetStaticMesh(CubeVisualAsset.Object);

		//初始化静态网格体组件的位置
		//VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); 
	//}
	// ------不推荐这种做法-----------
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	//第二种制作方法
	if (NewMesh != nullptr)
	{
		VisualMesh->SetStaticMesh(NewMesh);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//获取当前的位置
	FVector NewLocation = GetActorLocation();

	//获取当前旋转
	FRotator NewRotation = GetActorRotation();

	//获取当前游戏时间
	float RunningTime = GetGameTimeSinceCreation();

	//计算物体在下一帧相比当前帧，高度的变化。
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	//把物体位置的Z轴坐标，加上物体在下一帧相比当前帧，高度的变化，乘以20.0f。这样可以使得物体在下一帧相比当前帧，位置的变化，更加明显。
	//NewLocation.Z += DeltaHeight * 20.0f;

	//方法二:
	NewLocation.Z += DeltaHeight * FloatSpeed;

	//把物体旋转的Yaw轴坐标，加上当前游戏时间，乘以20.0f。这样可以使得物体在下一帧相比当前帧，旋转的变化，更加明显。
	//float DeltaRotation = RunningTime * 20.0f;

	//方法二:
	float DeltaRotation = RunningTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	//设置物体的位置和旋转
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

