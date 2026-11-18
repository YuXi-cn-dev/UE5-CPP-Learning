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

//集合查询
void ASetActor::QuerySet()
{
	TSet<FString> FruitSet;

	//如果value存在则返回true,并且进行后者替换前者
	bool bHave = false;
	FruitSet.Add(TEXT("A"), &bHave);

	//添加元素
	FruitSet.Add(TEXT("B"));
	FruitSet.Add(TEXT("C"));
	FruitSet.Add(TEXT("A"), &bHave);

	//记入元素
	int32 countSet = FruitSet.Num();

	//查询集合元素的值是否存在
	bool bHasA = FruitSet.Contains(TEXT("A"));
	bool bHasB = FruitSet.Contains(TEXT("ABCD"));

	//创建一个ID，集合通过ID进行字符串的拼接
	FSetElementId SetElementId = FruitSet.Add(TEXT("Water"));
	FruitSet[SetElementId] += TEXT("Modify");

	//通过Find查询这个集合元素的值是否存在，如果存在返回这个元素的指针
	FString* Ptr1 = FruitSet.Find(TEXT("A"));
	FString* Ptr2 = FruitSet.Find(TEXT("None"));

	//将无序的Set转为Array，以便后续通过索引或进行排序
	//注意:把旧的数组拷贝到新的数组时，无论新的数组是否有元素都会进行被覆盖.
	TArray<FString> FruitArray = FruitSet.Array();
}

//集合删除
void ASetActor::RemoveSet()
{
	TSet<FString> FruitSet;

	//预留空间，避免频繁扩容
	FruitSet.Reserve(4); 

	//添加元素
	FruitSet.Add("NPC");
	FruitSet.Add("Player");
	FruitSet.Add("Boss");

	// 通过底层元素 ID (索引 0) 直接移除。直接传 ID 可以避免计算哈希和查找，时间复杂度为 O(1)。
	FruitSet.Remove(FSetElementId::FromInteger(0));

	// 尝试从 FruitSet 中移除 "Player_0"，返回值为实际移除的数量（1表示成功，0表示原本就不存在）
	int32 RemoveSetNum1 = FruitSet.Remove(TEXT("Player"));

	// 尝试移除 "None"，同样记录移除数量
	int32 RemoveSetNum2 = FruitSet.Remove(TEXT("None"));

	//拷贝一份原集合以继承其底层内存大小，随后清空内容。
	TSet<FString> FruitSetAI = FruitSet;
	FruitSetAI.Reset();

	//清空集合
	FruitSet.Empty(0);
}

//集合排序
void ASetActor::SortSet()
{
	TSet<FString> FruitSet = { "B", "AD", "CE", "DF", "ENSQ", "F3", "G3", "HL", "IEC" };

	// 按照字符串大小排序
	FruitSet.Sort([](const FString& A, const FString& B) {
		return A > B;
		});

	// 按照字符串长度排序
	FruitSet.Sort([](const FString& A, const FString& B) {
		return A.Len() < B.Len(); 
	});
	
}

//集合操作符
void ASetActor::OperatorSet()
{
	TSet<FString> FruitSet = { "NPC","Player","Boss" };

	//集合赋值
	TSet<FString> NewSet = FruitSet;

	NewSet.Add(TEXT("Pear"));
	NewSet.Remove("Player");
}

//集合slack
void ASetActor::SlackSet()
{
	TSet<FString> FruitSet = { "NPC","Player","Boss" };
	FruitSet.Reset();

	FruitSet.Reserve(10);

	for (int32 i = 0; i < 10; ++i)
	{
		//添加元素
		FruitSet.Add(TEXT("NPC") + FString::FromInt(i));  
	}

	//删除元素
	for (int32 i = 0; i < 10; i+=2)
	{
		FruitSet.Remove(TEXT("NPC") + FString::FromInt(i));
	}

	FruitSet.Shrink();

	FruitSet.CompactStable();
	FruitSet.Shrink();
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

