// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapActor.generated.h"

UCLASS()
class TEST_API AMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapActor();

public:

//字典
#pragma region  Map

	UFUNCTION(BlueprintCallable)
	void InitMap();

	UFUNCTION(BlueprintCallable)
	void IterateMap();

	UFUNCTION(BlueprintCallable)
	void QueryMap();

	UFUNCTION(BlueprintCallable)
	void FindMap();

	UFUNCTION(BlueprintCallable)
	void FindAdvancedMap();

	UFUNCTION(BlueprintCallable)
	void FindKeyMap();
	
	UFUNCTION(BlueprintCallable)
	void FindGetAllKeysAndValueMap();

	UFUNCTION(BlueprintCallable,category = " RemoveMap")
	void RemoveMap();

	UFUNCTION(BlueprintCallable, category = " RemoveMap")
	void RemoveCheckMap();

	UFUNCTION(BlueprintCallable, category = " RemoveMap")
	void RemoveAndCopyValueMap();

	UFUNCTION(BlueprintCallable, category = " RemoveMap")
	void EmptyAndResetMap();

	UFUNCTION(BlueprintCallable, category = " Reverse")
	void ReverseMap();

	UFUNCTION(BlueprintCallable, category = "Sore")
	void SortMap();

	UFUNCTION(BlueprintCallable, category = "Operation")
	void OperatMap();

#pragma endregion  Map

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
	TMap<int, FString> MyFruitMap;

};
