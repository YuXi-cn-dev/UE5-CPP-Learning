// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrayActor.generated.h"

USTRUCT()
struct FAddStructInfo
{
	GENERATED_BODY()

public:
	FAddStructInfo()
	{
		UE_LOG(LogTemp, Warning, TEXT("我被初始化了0!!!"));
	}
	
	FAddStructInfo(int32 InHealth) : Healty(InHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("我被初始化了1!!!"));
	}
	
	~FAddStructInfo()
	{
		UE_LOG(LogTemp, Warning, TEXT("我被释放了!!!"));
	}
	

public:
	int32 Healty = 100;

};

USTRUCT()
struct FEqualStructInfo
{
	GENERATED_BODY()

public:
	FEqualStructInfo()
	{
		UE_LOG(LogTemp, Warning, TEXT("我被初始化了0!!!"));
	}

	FEqualStructInfo(int32 InID) : ID(InID)
	{
		UE_LOG(LogTemp, Warning, TEXT("我被初始化了1!!!"));
	}

	~FEqualStructInfo()
	{
		UE_LOG(LogTemp, Warning, TEXT("我被释放了!!!"));
	}

public:
	int32 ID = 0;

	bool operator==(const FEqualStructInfo& other) const
	{
		return ID == other.ID ? true : false;
	}

};

USTRUCT()
struct FSortStructInfo
{
	GENERATED_BODY()

public:
	FSortStructInfo() {}
	
	FSortStructInfo(int32 InID, int32 InMoney) : ID(InID), Money(InMoney)
	{
		
	}

	~FSortStructInfo() {}
	
public:
	int32 ID = 0;
	int32 Money = 0;

	bool operator<(const FSortStructInfo& other) const
	{
		return ID < other.ID ? true : false;
	}

};

USTRUCT()
struct FFindStructInfo
{
	GENERATED_BODY()

public:
	FFindStructInfo() {}

	FFindStructInfo(int32 InID, int32 InMoney) : ID(InID), Money(InMoney)
	{

	}

	~FFindStructInfo() {}

public:
	int32 ID = 0;
	int32 Money = 0;

	inline bool operator==(const int32 InID) 
	{
		return ID == InID ;
	}
};

inline bool operator==(const int32 InID, const FFindStructInfo InStruct)
{
	return InStruct.ID == InID ;
}



UCLASS()
class TEST_API AArrayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrayActor();

public:
	//作业: 1 (2026 - 9 - 1)  实现一个加法或者减法的函数以及创建变量
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 A = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 B = 0;

	UFUNCTION(BlueprintCallable)
	int32 AddNum(int32 x, int32 y);

	//作业: 2 (2026 - 9 - 2)  实现一个数组函数，并且可以遍历数组里面的元素
	UFUNCTION(BlueprintCallable)
	TArray<int32> GetIntArray();

	//作业: 3 (2026 - 9 - 5)  实现一个数组函数，并且可以对数组元素进行排序
	UFUNCTION(BlueprintCallable)
	TArray<int32> SortIntArray();

	//作业: 4 (2026 - 9 - 13)  实现一个数组函数，返回数组类型字节大小
	UFUNCTION(BlueprintCallable)
	uint8 Uint8TypeSize();

	//作业: 5 (2026 - 9 - 30)  通过给出的代码，来补充要求的代码.
	UFUNCTION(BlueprintCallable)
	void FilterAndProcessEnemies();

	//每周作业(2026 - 9 - 6): 实现一个数组函数，从最后一个元素遍历数组
	UFUNCTION(BlueprintCallable)
	TArray<FString> PrintArrayReverse();

public:

	UFUNCTION(BlueprintCallable)
	void InitIntArray();

	UFUNCTION(BlueprintCallable)
	void AddStrInitIntArray()
	{
		TArray<FString> StrArr;
		StrArr.Add("Hello");
		StrArr.Emplace(TEXT("World"));
	}

	//Add和Emplace的区别在与一个是临时构建,另外一个是拿对象进行构建，结束游戏后释放对象.
	UFUNCTION(BlueprintCallable)
	void AddStructArray();

	UFUNCTION(BlueprintCallable)
	void EmplaceStructArray();

	UFUNCTION(BlueprintCallable)
	TArray<FString> AppendStrArray();

	UFUNCTION(BlueprintCallable)
    void AddUniqueString();

	UFUNCTION(BlueprintCallable)
	TArray<FString> InsertString();

	UFUNCTION(BlueprintCallable)
	void SetStringNum();

	UFUNCTION(BlueprintCallable)
	void AddUniqueStruct();

//迭代
#pragma region ArrayRegion

	UFUNCTION(BlueprintCallable)
	void LoopArray();

	UFUNCTION(BlueprintCallable)
	void LoopArray1();

	UFUNCTION(BlueprintCallable)
	void LoopArray2();

	UFUNCTION(BlueprintCallable)
	void LoopArray_Right();

	UFUNCTION(BlueprintCallable)
	void LoopArray_Right2();

	UFUNCTION(BlueprintCallable)
	void TestLambda();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_Sort();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_HeapSort();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_StableSort();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_Sort_2();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_HeapSort_2();

	UFUNCTION(BlueprintCallable)
	TArray<FString> SortArray_StableSort_2();

	UFUNCTION(BlueprintCallable)
	void SortStructArray_StableSort();

#pragma endregion ArrayRegion

//查询
#pragma region Find

	UFUNCTION(BlueprintCallable)
	void FindArray();

	UFUNCTION(BlueprintCallable)
	void FindArray_Change();

	UFUNCTION(BlueprintCallable)
	void FindArray_Const();

	UFUNCTION(BlueprintCallable)
	void FindArray_ElementSize();

	UFUNCTION(BlueprintCallable)
	void FindArray_Index();

	UFUNCTION(BlueprintCallable)
	void FindArray_IsValid();

	UFUNCTION(BlueprintCallable)
	void FindArray_Upper();
 
	UFUNCTION(BlueprintCallable)
	void FindArray_Latest();

#pragma endregion Find

#pragma region Contain

	UFUNCTION(BlueprintCallable)
	void ContainArray();

	UFUNCTION(BlueprintCallable)
	void FindElementArray();

	UFUNCTION(BlueprintCallable)
	void FindElementByKey();

	UFUNCTION(BlueprintCallable)
	void FindElementRetPtr();

#pragma endregion Contain

//移除
#pragma region Remove

	UFUNCTION(BlueprintCallable)
	void RemoveElement();

	UFUNCTION(BlueprintCallable)
	void RemoveMultiElement();

	UFUNCTION(BlueprintCallable)
	void OperateArray();

	UFUNCTION(BlueprintCallable)
	void OperateStrArray();

#pragma endregion Remove

//数组堆
#pragma region  Heapon

	UFUNCTION(BlueprintCallable)
	void HeaponArray();

#pragma endregion  Heapon

//动态调整数组的大小
#pragma region  Slack

	UFUNCTION(BlueprintCallable)
	void SlackArray();

	UFUNCTION(BlueprintCallable)
	void SlackArray_Empty();

	UFUNCTION(BlueprintCallable)
	void SlackArray_Reset();

	UFUNCTION(BlueprintCallable)
	void ShrinkArray();

#pragma endregion  Slack

//原始内存
#pragma region Origin

	UFUNCTION(BlueprintCallable)
	void OriginArray();

	UFUNCTION(BlueprintCallable)
	void OriginStringArray();

	UFUNCTION(BlueprintCallable)
	void ZeroArray();

	UFUNCTION(BlueprintCallable)
	void ZeroAndUninitArray();

#pragma endregion  Origin

//其他
#pragma region  Other

	UFUNCTION(BlueprintCallable)
	void SwapArray();

	UFUNCTION(BlueprintCallable)
	void AddDefaultArray();
	UFUNCTION(BlueprintCallable)
	void ReserveArray();

#pragma endregion  Other


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FAddStructInfo> StructArray;
};
