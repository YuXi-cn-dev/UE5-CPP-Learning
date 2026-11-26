// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScalingBoxActor.generated.h"

UCLASS()
class TEST_API AScalingBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScalingBoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//EndPlay：游戏结束、Actor 被销毁、关卡切换时调用，适合做“收尾/停止”。
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	//创建静态网格体组件
	// VisibleAnywhere 表示在编辑器细节面板里能看到它
	UPROPERTY(VisibleAnywhere, Category = "YX")
	class UStaticMeshComponent* BoxMesh;

	//初始大小
	UPROPERTY(EditAnywhere, Category = "Scaling")
	FVector InitialScale;

	//运行时间
	float RunningTime;

	//变换速度
	UPROPERTY(EditAnywhere, Category = "Scaling")
	float ScaleSpeed = 1.0f;

	//最小缩放倍率：0.5 表示最小缩到初始大小的一半
	UPROPERTY(EditAnywhere, Category = "Scaling")
	float MinScaleRatio = 0.5;

	//最大缩放倍率：1.5 表示最大放大到初始大小的 1.5 倍
	UPROPERTY(EditAnywhere, Category = "Scaling")
	float MaxScaleRatio = 1.5;

	// 一个开关：true 表示正在变大变小，false 表示停止缩放
	bool bIsScaling ;
};
