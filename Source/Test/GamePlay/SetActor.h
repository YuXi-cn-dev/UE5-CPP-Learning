// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SetActor.generated.h"

UCLASS()
class TEST_API ASetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASetActor();

public:

//快速容器(集合)
#pragma region Set

	UFUNCTION(BlueprintCallable, Category = "Set")
	void InitSet();

	UFUNCTION(BlueprintCallable, Category = "Set")
	void LoopSet();

	UFUNCTION(BlueprintCallable, Category = "QuerySet")
	void QuerySet();

	UFUNCTION(BlueprintCallable, Category = "RemoveSet")
	void RemoveSet();

#pragma endregion Set


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Set")
	TSet<FString> MyFruitSet;
};
