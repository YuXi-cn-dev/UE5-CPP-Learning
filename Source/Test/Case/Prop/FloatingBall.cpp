// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingBall.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFloatingBall::AFloatingBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	
	RootComponent = BallMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/Mesh/Sphere.Sphere"));

	if (SphereMesh.Succeeded())
	{
		BallMesh->SetStaticMesh(SphereMesh.Object);
	}

	//设置物理效果
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	BallMesh->SetLinearDamping(1.0f);
}


// Called when the game starts or when spawned
void AFloatingBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//判断玩家是否靠近，如果靠近就"永久"关闭悬浮

	if (!bHasFallen)
	{
		//获取第一个玩家的Pawn
		APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

		if (Player)
		{
			//计算玩家和球之间的距离。
			//FVector::Dist(点1, 点2) -> 返回两点之间的直线距离，单位厘米。
			//点1: Player->GetActorLocation()获取玩家位置.
			//点2: GetActorLocation()获取Actor位置.
			const float Dist = FVector::Dist(Player->GetActorLocation(), GetActorLocation());

			//距离小于阈值，说明玩家靠近了
			if (Dist < TriggerRadius)
			{
				bHasFallen = true;

				UE_LOG(LogTemp, Warning, TEXT("玩家靠近，球开始掉落"));
			}
		}
	}
	
	//施加悬浮力
	if (!bHasFallen && BallMesh && BallMesh->IsSimulatingPhysics())
	{
		// ---- 计算悬浮力 ----

		//质量x重力加速度x倍数 -> 得到"抵消重力所需的力量"
		const float HoverForce = BallMesh->GetMass() * 980.0f * HoverStrength;

       //施加向上的力
		BallMesh->AddForce(FVector(0.0f, 0.0f, HoverForce));
	}
}

