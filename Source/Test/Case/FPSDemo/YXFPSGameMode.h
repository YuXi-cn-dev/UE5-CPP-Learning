// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YXFPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AYXFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	// 声明重写 StartPlay 函数
	virtual void StartPlay() override;
};
