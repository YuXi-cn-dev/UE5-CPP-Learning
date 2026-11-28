// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "YXPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UYXPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:

	//每帧更新
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
