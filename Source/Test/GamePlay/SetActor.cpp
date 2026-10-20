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

//集合迭代
void ASetActor::LoopSet()
{
	TSet<FString> FruitSet;

	//添加元素
	FruitSet.Add(TEXT("A"));
	FruitSet.Add(TEXT("B"));
	FruitSet.Add(TEXT("C"));

	//打印输出
	for (auto& Elem : FruitSet)
	{
		Elem += TEXT("1");
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("\"%s\"\n"), *Elem));
	}

	for (FString& Elem : FruitSet)
	{
		Elem += TEXT("2");
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("\"%s\"\n"), *Elem));
	}

	//非常量迭代器
	for (auto It = FruitSet.CreateIterator(); It; ++It)
	{
		(*It)+= TEXT("3");
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("(%s)\n"), *(*It)));
	}

	//常量迭代器
	for (auto It = FruitSet.CreateConstIterator(); It; ++It)
	{
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("(%s)\n"), *(*It)));
	}
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

