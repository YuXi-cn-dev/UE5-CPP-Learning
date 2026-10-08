// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor.h"

// Sets default values
AMapActor::AMapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

#pragma region  Map

//字典初始化和添加
void AMapActor::InitMap()
{
	TMap<int, FString> FruitMap;

	//添加字典元素
	FString& MyFruct = FruitMap.Add(1, TEXT("Apple")); 
	MyFruct+=TEXT("!!!!!!");

	FruitMap.Add(2, TEXT("Banana"));
	FruitMap.Add(3, TEXT("Cherry"));

	//覆盖key为2的元素的字符串.
	FruitMap.Add(2, TEXT("Peach"));

	//重新构建默认的字典
	FruitMap.Add(4);

	FruitMap.Emplace(5, TEXT("Orange"));

	//把FruitMap元素进行全部覆盖
	TMap<int, FString> FruitMap2;

	FruitMap.Add(1, TEXT("AAAA"));
	FruitMap.Add(2, TEXT("BBBB"));
	FruitMap.Add(3, TEXT("CCCC"));
	FruitMap.Append(FruitMap2);

	//数组元素为空时，当出现重复的key时，会自动添加到数组中
	TMultiMap<int, FString> FruitMultiMap;
	FruitMultiMap.Add(1, TEXT("A"));
	FruitMultiMap.Add(1, TEXT("B"));
	FruitMultiMap.Add(1, TEXT("C"));
}

//字典的迭代(遍历)
void AMapActor::IterateMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(1, TEXT("Apple"));
	FruitMap.Add(2, TEXT("Banana"));
	FruitMap.Add(3, TEXT("Cherry"));

	for (auto& Elem : FruitMap) 
	{
		//打印输出日志
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("Auto - (%d, \"%s\")\n"), Elem.Key, *Elem.Value));
		UE_LOG(LogTemp, Warning, TEXT("Auto - (%d, \"%s\")\n"), Elem.Key, *Elem.Value);
	}

	for (const TPair<int, FString>& Element : FruitMap)
	{
		FString Message = FString::Printf(TEXT("TPair - (%d, \"%s\")\n"), Element.Key, *Element.Value);
		UE_LOG(LogTemp, Warning, TEXT("%s,%s"),*FString(__FUNCTION__),*Message);
		FPlatformMisc::LocalPrint(*Message);
	}
	
	for (auto It = FruitMap.CreateConstIterator(); It; ++It)
	{
		FPlatformMisc::LocalPrint(*FString::Printf(TEXT("Iterator - (%d, \"%s\")\n"), It.Key(), *It.Value()));
	}
}

//普通查询字典
void AMapActor::QueryMap()
{
	TMap<int, FString> FruitQueryMap;
	FruitQueryMap.Add(5, TEXT("Apple"));
	FruitQueryMap.Add(7, TEXT("Banana"));
	FruitQueryMap.Add(9, TEXT("Cherry"));

	//查询字典元素有多少?
	int32 Count = FruitQueryMap.Num();

	//查询字典元素的key值是否存在
	bool bHas7 = FruitQueryMap.Contains(7);
	bool bHas8 = FruitQueryMap.Contains(8);

	//拷贝方式拿到字典元素的值
	FString Val7 = FruitQueryMap[7];
	Val7+=TEXT("Copy!");

	//引用方式拿到字典元素的值
	FString& Val7Ref = FruitQueryMap[7];
	Val7Ref += TEXT("Ref!!");

	//常量引用方式拿到字典元素的值
	const FString& Val7ConstRef = FruitQueryMap[7];

	if (bHas8)
	{
		FString Val8 = FruitQueryMap[8];
	}
}

void AMapActor::FindMap()
{
	TMap<int, FString> FruitFindMap;
	FruitFindMap.Add(5, TEXT("Apple"));
	FruitFindMap.Add(7, TEXT("Banana"));
	FruitFindMap.Add(9, TEXT("Cherry"));

	FString* Ptr7 = FruitFindMap.Find(7);
	FString* Ptr8 = FruitFindMap.Find(8);

	if (FString* Ptr7Test = FruitFindMap.Find(7))
	{
		UE_LOG(LogTemp, Warning, TEXT("%d - %s"),7,**Ptr7Test);
	}
}

//高级查询字典
void AMapActor::FindAdvancedMap()
{
	TMap<int, FString> FruitAdvFindMap;
	FruitAdvFindMap.Add(5, TEXT("Apple"));
	FruitAdvFindMap.Add(7, TEXT("Banana"));
	FruitAdvFindMap.Add(9, TEXT("Cherry"));

	//可能会创建的新的元素，返回是引用
	FString& Ref7 = FruitAdvFindMap.FindOrAdd(7);
	FString& Ref8 = FruitAdvFindMap.FindOrAdd(8);
	Ref8+=TEXT("New Add 8!");

	//不会创建新的元素，如果没有就构建一个临时的默认返回值，返回的是副本的值
	FString val7 = FruitAdvFindMap.FindRef(7);
	val7+=TEXT("996");
	FString val6 = FruitAdvFindMap.FindRef(6);
}

void AMapActor::FindKeyMap()
{
	TMap<int, FString> FruitKeyMap;
	FruitKeyMap.Add(5, TEXT("Melon"));
	FruitKeyMap.Add(1, TEXT("Pineaqpple"));
	FruitKeyMap.Add(3, TEXT("Pineaqpple"));
	FruitKeyMap.Add(10,TEXT("Pineaqpple"));

	//通过value的值去找Key.
	const int32* KeyPtr7 = FruitKeyMap.FindKey(TEXT("Melon"));
	const int32* KeyPtr8 = FruitKeyMap.FindKey(TEXT("Kumquat"));

	const int32* KeyFindTest1 = FruitKeyMap.FindKey(TEXT("Pineaqpple"));
	FruitKeyMap.Add(11, TEXT("Pineaqpple"));
	FruitKeyMap.Add(12, TEXT("Pineaqpple"));
	FruitKeyMap.Add(13, TEXT("Pineaqpple"));

	const int32* KeyFindTest2 = FruitKeyMap.FindKey(TEXT("Pineaqpple"));
}

void AMapActor::FindGetAllKeysAndValueMap()
{
	TMap<int, FString> FruitAdvFindMap;
	FruitAdvFindMap.Add(5, TEXT("Apple"));
	FruitAdvFindMap.Add(7, TEXT("Melon"));
	FruitAdvFindMap.Add(9, TEXT("Pineaqpple"));

	//获取所有的key和value
	TArray<int32> Keys;
	TArray<FString> Values;

	//GenerateKeyArray()  -> 生成key数组
	//GenerateValueArray() -> 生成value数组
	FruitAdvFindMap.GenerateKeyArray(Keys);
	FruitAdvFindMap.GenerateValueArray(Values);
}

//字典移除
void AMapActor::RemoveMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(1, TEXT("AAAA"));
	FruitMap.Add(2, TEXT("BBBB"));
	FruitMap.Add(3, TEXT("CCCC"));

	//删除字典元素
	FruitMap.Remove(1);

    //返回移除后，数组里面的元素个数
	int32 Key2ToTemove = FruitMap.Remove(2);
	int32 Key4ToTemove = FruitMap.Remove(4);
}

void AMapActor::RemoveCheckMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(1, TEXT("Apple"));
	FruitMap.Add(2, TEXT("Melon"));
	FruitMap.Add(3, TEXT("Pineaqpple"));

	//查找key对应的Value，如果存在就移除，并且返回key对应的Value(谨慎使用这个函数)
	FString Remove1 = FruitMap.FindAndRemoveChecked(1);
	//FString Remove2 = FruitMap.FindAndRemoveChecked(4);
}

void AMapActor::RemoveAndCopyValueMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(1, TEXT("AAAA"));
	FruitMap.Add(2, TEXT("BBBB"));
	FruitMap.Add(3, TEXT("CCCC"));

	//通过key找到对应的value值，如果存在就移除并拷贝value值，返回移除后的value值
	FString Removed = TEXT("None"); //初始化
	bool bRemove1 = FruitMap.RemoveAndCopyValue(1, Removed);
	bool bRemove2 = FruitMap.RemoveAndCopyValue(4, Removed);
}

void AMapActor::EmptyAndResetMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(1, TEXT("Apple"));
	FruitMap.Add(2, TEXT("Banana"));
	FruitMap.Add(3, TEXT("Cherry"));

	//Empty和Reset的区别:
	//1.Empty()  ->  清空数组，但是不删除数组
	//2.Empty(2) ->  清空数组，但是不删除数组，并且设置最大容量
	FruitMap.Empty();
	FruitMap.Empty(2);
	
	//3.Reset()  ->  清空数组，并且删除数组,保留最大容量
	FruitMap.Reset();
}

//在字典数组中进行预留容量空间
void AMapActor::ReverseMap()
{
	TMap<int, FString> FruitMap;;
	FruitMap.Add(1, TEXT("AAAA"));
	FruitMap.Add(2, TEXT("BBBB"));
	FruitMap.Add(3, TEXT("CCCC"));

	//给字典数组预留足够空间
	FruitMap.Reserve(10);
}

//对字典数组的key值和value值进行排序
void AMapActor::SortMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(4, TEXT("SDDDD"));
	FruitMap.Add(3, TEXT("CC"));
	FruitMap.Add(2, TEXT("B"));
	FruitMap.Add(1, TEXT("None"));

	FString* MyFruit = FruitMap.Find(2);
	if (MyFruit)
	{
		(*MyFruit)+=TEXT("M1");
	}


	//对字典数组的key值进行排序进行排序
	FruitMap.KeySort([](int32 Key1, int32 Key2) {

		return Key1 > Key2;
	});

	//对字典数组的value值进行排序进行排序
	FruitMap.ValueSort([](const FString& Value1, const FString& Value2) {

		return Value1.Len() < Value2.Len();

		});

	(*MyFruit) += TEXT("M2");

	int32 Count = 1;

}

//字典运算符
void AMapActor::OperatMap()
{
	TMap<int, FString> FruitMap;
	FruitMap.Add(7, TEXT("Pineaqpple"));
	FruitMap.Add(5, TEXT("Melon"));
	FruitMap.Add(10, TEXT("Cherry"));

	//把FruitMap元素赋予NewMap，并且修改NewMap的key5的值.
	TMap<int, FString> NewMap = FruitMap;
	NewMap[5] = TEXT("apple");

	NewMap.Remove(1);

	//MoveTemp(FruitMap) -> 移动FruitMap的元素到NewMap2中，FruitMap的元素被清空
	TMap<int, FString> NewMap2 = MoveTemp(FruitMap);

	//创建一个Actor类型字典，并且添加key和value.
	TMap<int32,AActor*> MyActorPtrs;
	MyActorPtrs.Add(1, this);
	MyActorPtrs.Add(2, nullptr);
	MyActorPtrs.Add(3, nullptr);
	
	//把MyActorPtrs的元素赋值给MyAnotherActorPtrs，并且修改MyAnotherActorPtrs的key1的值
	TMap<int32, AActor*> MyAnotherActorPtrs = MyActorPtrs;
	MyAnotherActorPtrs[1]->SetActorLocation(FVector::ZeroVector);
	MyActorPtrs[1]->SetActorLocation(FVector::ZeroVector);

	//比较两个字典数组是否相等
	bool Equal = MyActorPtrs[1] == MyAnotherActorPtrs[1];
}

//字典的堆
void AMapActor::SlackMap()
{
	TMap<int, FString> FruitMap;

	//预留空间
	FruitMap.Reserve(5);

	//添加元素
	FruitMap.Add(1, TEXT("Pineaqpple"));
	FruitMap.Add(2, TEXT("Melon"));
	FruitMap.Add(3, TEXT("Cherry"));

	//移除
	FruitMap.Remove(2);

	//FruitMap.Shrink() ->缩容:释放多余的内存给系统
	FruitMap.Shrink();

	//FruitMap.Compact() ->紧凑:移除删除元素留下的空洞，但不释放总容量
	FruitMap.Compact();
	FruitMap.Shrink();
}

//字典的重载运算符
void AMapActor::StructMap()
{
	TMap<FMapInfo, int32> MyAIs;

	MyAIs.Add(FMapInfo(TEXT("NPC")), 1);
	MyAIs.Add(FMapInfo(TEXT("Player")), 2);
	MyAIs.Add(FMapInfo(TEXT("BOSS")), 3);

	//如果key存在，返回key对应的value，如果key不存在，创建key并返回默认值,并且保证有Value的值有4个.
	MyAIs.FindOrAdd(FMapInfo(TEXT("NormalEnemy")), 4);

	//查找键为"Player"的值，如果不存在则自动添加(默认值为0),并且保证至少有2个玩家.
	int32& PlayerNum = MyAIs.FindOrAdd(FMapInfo(TEXT("Player")));

	//找到或者创建后，计数加一
	PlayerNum+=1;
}



#pragma endregion  Map

// Called when the game starts or when spawned
void AMapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

