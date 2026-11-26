// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "YXPawnWithCamera.generated.h"

UCLASS()
class TEST_API AYXPawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AYXPawnWithCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	//1. W、A、S、D
	void YXMoveForward(float AxisValue);
	void YXMoveRight(float AxisValue);

	//2. 鼠标上下左右滑动
	void YXPitchCamera(float AxisValue);
	void YXYawCamera(float AxisValue);

	//3. 鼠标滚轮
	void YXZoomIn();
	void YXZoomOut();

protected:
	// 1. 声明一个弹簧臂组件指针
	UPROPERTY(EditAnywhere, Category = "YX")
	class USpringArmComponent* SpringArmComp;

	// 2. 声明一个摄像机组件指针
	UPROPERTY(EditAnywhere, Category = "YX")
	class UCameraComponent* CameraComp;

	// 3. 声明一个静态网格体组件指针
	UPROPERTY(EditAnywhere, Category = "YX")
	class UStaticMeshComponent* StaticMeshComp;

	//1. 记录走路的指令
	FVector2D MovementInput;

	//2. 记录转视角的指令
	FVector2D CameraInput;

	//3. 记录缩放的大小
	float ZoomFactor = 1.0f;

	//4. 记录是否正在“瞄准/放大”
	bool bZoomIn = false;

};
