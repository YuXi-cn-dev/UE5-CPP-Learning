// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayQuiz.h"

// Sets default values
AGameplayQuiz::AGameplayQuiz()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// =============================================================
// 第 1 题：战利品堆叠合并
// =============================================================
TArray<FItemStack> AGameplayQuiz::MergeItemStacks(const TArray<FItemStack>& Input) const
{
    TArray<FItemStack> Result;
    Result.Reserve(Input.Num());

    TMap<FName, int32> IndexByItemID;
    IndexByItemID.Reserve(Input.Num());

    for (const FItemStack& Stack : Input)
    {
        if (Stack.Count <= 0)
        {
            continue;
        }

        // 空1：在 TMap 中查找 ItemID 对应的结果下标
        //if (int32* FoundIndex = IndexByItemID.______(Stack.ItemID))
        //{
            // FoundIndex 是指针，*FoundIndex 才是它指向的下标值
            //Result[*FoundIndex].Count += Stack.Count;
        //}
        //else
        //{
            // 空2：记录 ItemID 在 Result 中的下标
            //IndexByItemID.______(Stack.ItemID, Result.Num());

            // 空3：把当前堆叠加入结果数组
            //Result.______(Stack);
       // }
    }

    return Result;
}

// =============================================================
// 第 2 题：重生点筛选
// =============================================================
TArray<FVector> AGameplayQuiz::PickNearestSpawnPoints(
    const TArray<FVector>& Candidates,
    const TSet<FVector>& Occupied,
    const FVector& PlayerLocation,
    int32 MaxCount) const
{
    TArray<FVector> ValidPoints;
    if (MaxCount <= 0)
    {
        return ValidPoints;
    }

    ValidPoints.Reserve(Candidates.Num());

    TSet<FVector> SeenPoints;
    SeenPoints.Reserve(Candidates.Num());

    for (const FVector& Point : Candidates)
    {
        // 空1：排除已被占用的点
        //if (Occupied.______(Point))
        //{
           //continue;
       // }

        // 空2：判断这个点是否已经出现过
        //if (SeenPoints.______(Point))
        //{
            //continue;
        //}

        // 空3：把这个点记录到去重集合中
        //SeenPoints.______(Point);
        ValidPoints.Add(Point);
    }

    // 空4：按距离玩家从近到远排序
    // Sort 的参数是 Lambda；Lambda 返回 true 表示 A 排在 B 前面
    // DistSquared 是距离平方，比较大小和真实距离一致，但不用开平方
   // ValidPoints.______([&PlayerLocation](const FVector& A, const FVector& B)
        //{
            //return FVector::DistSquared(A, PlayerLocation)
                //< FVector::DistSquared(B, PlayerLocation);
       // });

    //if (ValidPoints.Num() > MaxCount)
    //{
    //    // 空5：只保留前 MaxCount 个
    //    ValidPoints.______(MaxCount);
    //}

    return ValidPoints;
}

// =============================================================
// 第 3 题：任务进度批量结算
// =============================================================
TArray<FName> AGameplayQuiz::ApplyQuestProgress(
    TMap<FName, FQuestState>& Quests,
    const TMap<FName, int32>& Deltas) const
{
    TArray<FName> NewlyCompleted;
    NewlyCompleted.Reserve(Deltas.Num());

    // TMap 遍历用 TPair，Pair.Key 是任务 ID，Pair.Value 是增量
    for (const TPair<FName, int32>& Pair : Deltas)
    {
        if (Pair.Value <= 0)
        {
            continue;
        }

        // 空1：从 Quests 中查找任务状态
        //FQuestState* State = Quests.______(Pair.Key);

        // State 是指针，必须判空，否则访问会崩溃
        /*if (!State || State->bCompleted)
        {
            continue;
        }*/

        // 空2：增加进度，但不要超过 Target
        //State->Current = FMath::______(
        //    State->Current + Pair.Value,
        //    State->Target);

        //if (State->Current >= State->Target)
        //{
        //    // 空3：标记任务完成
        //    State->bCompleted = ______;

        //    // 空4：把刚完成的任务 ID 加入返回数组
        //    NewlyCompleted.______(Pair.Key);
        //}
    }

    return NewlyCompleted;
}

// =============================================================
// 第 4 题：AOE 伤害统计与排名
// =============================================================

TArray<AActor*> AGameplayQuiz::GetTopDamageTargets(
    const TArray<FHitInfo>& Hits,
    const TSet<AActor*>& ImmuneActors,
    AActor* InInstigator,
    int32 TopN) const
{
    TArray<AActor*> Result;
    if (TopN <= 0)
    {
        return Result;
    }

    TMap<AActor*, int32> DamageMap;
    DamageMap.Reserve(Hits.Num());

    for (const FHitInfo& Hit : Hits)
    {
        AActor* Target = Hit.Target;

        if (!IsValid(Target)
            || Target == InInstigator
            // 空1：过滤免疫目标
            //|| ImmuneActors.______(Target)
            || Hit.Damage <= 0)
        {
            continue;
        }

        // 空2：拿到这个目标的总伤害，没有就新建一个 0
        //int32& TotalDamage = DamageMap.______(Target);
        //TotalDamage += Hit.Damage;
    }

    TArray<TPair<AActor*, int32>> Ranked;
    Ranked.Reserve(DamageMap.Num());
    for (const TPair<AActor*, int32>& Pair : DamageMap)
    {
        // 空3：把键值对加入数组
        //Ranked.______(Pair);
    }

    // 空4：按总伤害从高到低排序
   // Ranked.______([](const TPair<AActor*, int32>& A,
        /*const TPair<AActor*, int32>& B)
        {
            return A.Value > B.Value;
        });*/

    // 空5：取 TopN 和数组长度中较小的那个
    /*const int32 Count = FMath::______(TopN, Ranked.Num());
    for (int32 Index = 0; Index < Count; ++Index)
    {
        Result.Add(Ranked[Index].Key);
    }*/

    return Result;
}

// Called when the game starts or when spawned
void AGameplayQuiz::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameplayQuiz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

