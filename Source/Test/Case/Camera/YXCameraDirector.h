// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YXCameraDirector.generated.h"

UCLASS()
class TEST_API AYXCameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYXCameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(EditAnywhere, Category = "YX")

	// 声明一个指向 Actor 的指针，用来存放“摄像机1”的引用
	AActor* CameraOne; 

	UPROPERTY(EditAnywhere, Category = "YX")

	// 声明一个指向 Actor 的指针，用来存放“摄像机2”的引用
	AActor* CameraTwo; 

	// 声明一个浮点数秒表变量，初始值为 0.0f。
	float TimeToNexCameraChange = 0.f;

};
