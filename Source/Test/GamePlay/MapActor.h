// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapActor.generated.h"

USTRUCT()
struct FMapInfo
{
	GENERATED_BODY()

	int32 Health = -1;

	FString AIName = TEXT("None");

	FMapInfo() {}
	
	FMapInfo(FString InAIName):AIName(InAIName) {}
	
	~FMapInfo() {}

	bool operator==(const FMapInfo& Other) const
	{
		return AIName == Other.AIName ? true : false;
	}

	friend uint32 GetTypeHash(const FMapInfo& Other) 
	{
		return GetTypeHash(Other.AIName); 
	}
};

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

	UFUNCTION(BlueprintCallable, category = "Slack")
	void SlackMap();

	UFUNCTION(BlueprintCallable, category = "StructMap")
	void StructMap();


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
