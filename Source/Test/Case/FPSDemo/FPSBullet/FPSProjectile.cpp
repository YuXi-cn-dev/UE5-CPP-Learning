// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建发射物静态网格体组件
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

	//添加球体静态网格体
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMesh(TEXT("/Game/Mesh/Sphere.Sphere"));

	//添加资源
	if (ProjectileMesh.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(ProjectileMesh.Object);
	}

	//创建球体碰撞组件
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	//设置球体碰半径
	CollisionComponent->InitSphereRadius(15.0f);

    //把根组件设置碰撞组件
	RootComponent = CollisionComponent;

	//创建发射物移动组件
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	// 将抛射物移动组件的 UpdatedComponent 设置为 CollisionComponent
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

	// 设置抛射物初始速度大小为 3000 cm/s（约 30 m/s）
	ProjectileMovementComponent->InitialSpeed = 3000.0f;

	// 设置抛射物最大速度大小为 3000 cm/s（约 30 m/s）
	ProjectileMovementComponent->MaxSpeed = 3000.0f;

	// 让抛射物旋转跟随速度方向，使其始终朝向飞行方向
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	// 允许抛射物在碰撞后反弹
	ProjectileMovementComponent->bShouldBounce = true;

	// 弹跳弹性系数设为 0.3
	ProjectileMovementComponent->Bounciness = 0.3f;

	// 关闭抛射物重力影响
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// 在构造函数中静态加载基础材质资源
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Material/M_Sphere.M_Sphere"));

	// 如果材质资源加载成功
	if (Material.Succeeded())
	{
		//加载材质资源
		BaseMaterial = Material.Object;

		// 把这个材质赋给网格体的第 0 个插槽
		ProjectileMeshComponent->SetMaterial(0, BaseMaterial);
	}
	
	// 设置网格体的相对缩放为 0.09，调整到合适大小
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));

	// 将网格体挂载到 Actor 的根组件上，使其跟随 Actor 移动
	ProjectileMeshComponent->SetupAttachment(RootComponent);
}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	// 用发射方向 × 初始速度大小，得到完整的速度向量并赋给移动组件。
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

