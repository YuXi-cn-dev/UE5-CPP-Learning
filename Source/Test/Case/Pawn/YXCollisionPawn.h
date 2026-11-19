// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "YXCollisionPawn.generated.h"

UCLASS()
class TEST_API AYXCollisionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AYXCollisionPawn();

	// 重写获取移动组件的函数
	virtual UPawnMovementComponent* GetMovementComponent()const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//声明一个粒子组件指针
	UPROPERTY()
	class UParticleSystemComponent* OurParticleSystem;

	//声明一个自定义的移动组件指针
	UPROPERTY()
	class UYXPawnMovementComponent* OurMovementComponent;

	//接收玩家按键输入
	void YXMoveForward(float AxisValue);

	void YXMoveRight(float AxisValue);

	void Turn(float AxisValue);

	void ParticleToggle();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
