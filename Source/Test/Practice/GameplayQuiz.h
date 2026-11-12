// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayQuiz.generated.h"

USTRUCT(BlueprintType)
struct FItemStack
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
    FName ItemID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
    int32 Count = 0;
};

USTRUCT(BlueprintType)
struct FQuestState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    int32 Current = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    int32 Target = 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    bool bCompleted = false;
};

USTRUCT(BlueprintType)
struct FHitInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hit")
    AActor* Target = nullptr;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hit")
    int32 Damage = 0;
};

/**
 * Gameplay 笔试 Actor
 * 所有题目函数都是 Actor 的成员函数，直接在 Actor 内实现。
 */

UCLASS()
class TEST_API AGameplayQuiz : public AActor
{
	GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AGameplayQuiz();
 

    // 第 1 题：战利品堆叠合并
    UFUNCTION(BlueprintCallable, Category = "Quiz")
    TArray<FItemStack> MergeItemStacks(const TArray<FItemStack>& Input) const;

    // 第 2 题：重生点筛选
    TArray<FVector> PickNearestSpawnPoints(
        const TArray<FVector>& Candidates,
        const TSet<FVector>& Occupied,
        const FVector& PlayerLocation,
        int32 MaxCount) const;

    // 第 3 题：任务进度批量结算
    TArray<FName> ApplyQuestProgress(
        TMap<FName, FQuestState>& Quests,
        const TMap<FName, int32>& Deltas) const;

    // 第 4 题：AOE 伤害统计与排名
    UFUNCTION(BlueprintCallable, Category = "Quiz")
    TArray<AActor*> GetTopDamageTargets(
        const TArray<FHitInfo>& Hits,
        const TSet<AActor*>& ImmuneActors,
        AActor* InInstigator,
        int32 TopN) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
