// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YXCameraDirectorModify.generated.h"

USTRUCT()
struct FToggleCameraInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "YX")
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, Category = "YX")
	float CameraBlendTime = 1.0f;
};


UCLASS()
class TEST_API AYXCameraDirectorModify : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYXCameraDirectorModify();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// 存储所有摄像机信息的列表
	UPROPERTY(VisibleAnywhere, Category = "YX")
	TArray<FToggleCameraInfo> CameraInfoList;

	float TimeToNexCameraChange = 0.f;

	//当前还没有选中任何摄像机
	int32 CameraIndex = -1;
};
