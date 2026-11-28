// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class TEST_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

	// 添加发射物静态网格体组件
	UPROPERTY(VisibleAnywhere, Category = "ProjectileMesh")
	UStaticMeshComponent* ProjectileMeshComponent;

	// 添加球体碰撞组件
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	USphereComponent* CollisionComponent;

	// 添加发射物移动组件
	UPROPERTY(VisibleAnywhere, Category = "Move")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// 用于保存加载到的基础材质
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UMaterialInterface* BaseMaterial;

	// 添加发射物的动态材质实例
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UMaterialInstanceDynamic* ProjectileMaterialInstance;


	// 初始化射击方向上发射物速度
	void FireInDirection(const FVector& ShootDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
