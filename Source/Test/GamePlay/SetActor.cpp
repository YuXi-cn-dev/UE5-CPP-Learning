// Fill out your copyright notice in the Description page of Project Settings.


#include "SetActor.h"

// Sets default values
ASetActor::ASetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

#pragma region  TSet

//集合初始化和添加
void ASetActor::InitSet()
{
	TSet<FString> FruitSet;

	//添加元素
	FruitSet.Add(TEXT("A"));
	FruitSet.Add(TEXT("B"));
	FruitSet.Add(TEXT("C"));

	FruitSet.Add(TEXT("D"));
	FruitSet.Add(TEXT("A"));

	FruitSet.Emplace(TEXT("Hello"));

	TSet<FString> FruitSet2;
	FruitSet2.Emplace(TEXT("World!"));

	FruitSet.Append(FruitSet2);
}


#pragma endregion  TSet

// Called when the game starts or when spawned
void ASetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

