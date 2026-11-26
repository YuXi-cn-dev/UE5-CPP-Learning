// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingBall.generated.h"

UCLASS()
class TEST_API AFloatingBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingBall();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent*  BallMesh;

	// ---- 新增：悬浮力相对重力的倍数 ----
	// meta = (ClampMin = "0.0", ClampMax = "3.0")：限定可调范围，避免误填出诡异数值
	UPROPERTY(EditAnywhere, Category = "Hover", meta = (ClampMin = "0.0", ClampMax = "3.0"));

	// 1.0 = 正好抵消重力；<1 会往下沉；>1 会往上飘
	float HoverStrength = 1.0f;

	//触发掉落所需的距离
	UPROPERTY(EditAnywhere, Category = "Trigger", meta = (ClampMin = "0.0"))
	float TriggerRadius = 300.f;

	//是否落地
	UPROPERTY(EditAnywhere, Category = "Fallen")
	bool bHasFallen = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
