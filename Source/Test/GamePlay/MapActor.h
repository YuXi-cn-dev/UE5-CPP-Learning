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

struct FMyStruct 
{
	FString UniqueID = TEXT(""); 
	float SomeFloat = 0.f;

	//显示构造函数:自动生成唯一ID(钥匙),并保存传入的浮点数据
	explicit FMyStruct(float InFloat) : UniqueID(FGuid::NewGuid().ToString()), SomeFloat(InFloat)
	{

	}
};

//字典键规则:指定以FMyStruct中的FString(唯一ID)作为TMap的键
template<typename ValueType>
struct TMyStructMapKeyFun : BaseKeyFuncs<TPair<FMyStruct, ValueType>, FString>
{
private:
	//定义基类别名Super，避免重复书写复杂的模本参数
	typedef BaseKeyFuncs<TPair<FMyStruct, ValueType>, FString> Super;

public:

	//定义基类的ElementInitType类型
	typedef typename Super::ElementInitType ElementInitType;

	//定义基类的ElmentKeyType类型
	typedef typename  Super::KeyInitType KeyInitType;

public:
	//1.告诉系统怎么从卡片里拔出"钥匙"（提取唯一ID字符串）
	static KeyInitType GetSetKey(ElementInitType Elment)
	{
		return Elment.Key.UniqueID;
	}

	//2.告诉系统怎么比较两个"钥匙"是否匹配（严格区分大小写，必须完全一致）
	static bool Matches(KeyInitType X, KeyInitType Y)
	{
		return X.Compare(Y, ESearchCase::CaseSensitive) == 0;
	}

	//3.告诉系统怎么给"钥匙"的算个快速指纹,用于大柜子极速查找
	static uint32 GetKeyHash(KeyInitType key)
	{
		return FCrc::StrCrc32(*key);
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

	UFUNCTION(BlueprintCallable, Category = " FindMap")
	void QueryMap();

	UFUNCTION(BlueprintCallable, Category = " FindMap")
	void FindMap();

	UFUNCTION(BlueprintCallable, Category = " FindMap")
	void FindAdvancedMap();

	UFUNCTION(BlueprintCallable, Category = " FindMap")
	void FindKeyMap();
	
	UFUNCTION(BlueprintCallable, Category = " FindMap")
	void FindGetAllKeysAndValueMap();

	UFUNCTION(BlueprintCallable, Category = " RemoveMap")
	void RemoveMap();

	UFUNCTION(BlueprintCallable, Category = " RemoveMap")
	void RemoveCheckMap();

	UFUNCTION(BlueprintCallable, Category = " RemoveMap")
	void RemoveAndCopyValueMap();

	UFUNCTION(BlueprintCallable, Category = " RemoveMap")
	void EmptyAndResetMap();

	UFUNCTION(BlueprintCallable, Category = " Reverse")
	void ReverseMap();

	UFUNCTION(BlueprintCallable, Category = "Sore")
	void SortMap();

	UFUNCTION(BlueprintCallable, Category = "Operation")
	void OperatMap();

	UFUNCTION(BlueprintCallable, Category = "Slack")
	void SlackMap();

	UFUNCTION(BlueprintCallable, Category = "StructMap")
	void StructMap();

	UFUNCTION(BlueprintCallable, Category = "StructMap")
	void StructKeyFunMap();

	UFUNCTION(BlueprintCallable, Category = "StructMap")
	void StructSize();

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
