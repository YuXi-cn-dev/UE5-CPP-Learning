// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YXFPSCharacter.generated.h"

UCLASS()
class TEST_API AYXFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYXFPSCharacter();

	//声明一个摄像机组件指针
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPSCameraComponent;

	//声明一个第一人称网格体组件指针，可以对所属玩家可见
	//TObjectPtr 是 UE5 推荐的智能指针
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> FPSMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//创建前后左右移动输入
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	//创建跳跃输入
	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
