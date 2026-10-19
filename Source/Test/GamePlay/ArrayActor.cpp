// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrayActor.h"

// Sets default values
AArrayActor::AArrayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

int32 AArrayActor::AddNum(int32 x, int32 y)
{
	return x + y;
}

TArray<int32> AArrayActor::GetIntArray()
{
	TArray<int32> Intarr = { 0 };//初始化

	Intarr.SetNum(20);//数组容量扩容

	Intarr = { 1,2,3,4,5,6 };

	//增
	Intarr.AddUnique(8);

	//删
	Intarr.Remove(3);

	//改
	Intarr.Insert(99, 3);//在第3个元素，插入99

	//查
	bool IsIntarr = false;
	if (Intarr.Find(3))
	{
		IsIntarr = true;
		return Intarr;
	}

	return Intarr;
}

TArray<int32> AArrayActor::SortIntArray()
{
	TArray<int32> Intarray = { 3,2,5,4,8,9,1,6,7 };
	Intarray.StableSort();
	return Intarray;
}

uint8 AArrayActor::Uint8TypeSize()
{
	TArray<uint8> Uint8Arr = { 0,1,2,3,4,5,6 };
	uint8 Uint8BySize = Uint8Arr.GetTypeSize();
	return Uint8BySize;
}

void AArrayActor::FilterAndProcessEnemies()
{
	// 初始数据：包含空名字、短名字、长名字
	TArray<FString> EnemyNames = { "Goblin", "", "Dragon", "Slime", "", "Orc", "DemonKing" };

	// ==========================================
	// TODO 1：过滤掉所有空名字（""），生成一个新数组 ValidEnemies。
	// 提示：使用 FilterByPredicate
	TArray<FString> ValidEnemies;
	// 你的代码...

	// ==========================================
	// TODO 2：将 ValidEnemies 中所有长度大于 5 的名字删除。
	// 要求：必须使用“不保持顺序、性能极高”的 Swap 系列删除法。
	// 提示：使用 RemoveAllSwap
	// 你的代码...

	// ==========================================
	// TODO 3：如果 ValidEnemies 里元素数量 >= 2，交换前两个元素的位置。
	// 要求：先判断索引是否有效（安全第一），再使用 UE 的交换函数。
	// 提示：使用 IsValidIndex 和 Exchange
	// 你的代码...

	// ==========================================
	// TODO 4：将 ValidEnemies 的资源全部“搬家”给 FinalEnemies，并让 ValidEnemies 彻底释放所有内存（容量归零）。
	// 提示：使用 MoveTemp 与 Empty() 两种选一即可
	TArray<FString> FinalEnemies;
	// 你的代码...

	// ==========================================
	// 测试输出（写完之后看这里验证）
	for (const FString& Name : FinalEnemies)
	{
		UE_LOG(LogTemp, Warning, TEXT("最终存活怪物: %s"), *Name);
	}
}

TArray<FString> AArrayActor::PrintArrayReverse()
{
	TArray<FString> StringArray = { "My","Name","is","Yu","Xi" };
	TArray<FString> MyStringArray;
	for (int32 index = StringArray.Num() - 1; index >= 0; index--)
	{
		MyStringArray.Add(StringArray[index]);
	}
	return MyStringArray;
}

void AArrayActor::InitIntArray()
{
	TArray<int32> IntArray1;
	TArray<int32> IntArray2;

	int32 ArrayNum1 = IntArray1.Num();//返回数组元素
	int32 ArraySize1 = IntArray2.GetAllocatedSize();//计算元素大小

	//初始化
	IntArray1.Init(10, 5);//IntArray1 = { 10,10,10,10,10 }
	IntArray2 = { 0,1,2,3 ,4,5,6 };

	int32 ArrayNum2 = IntArray1.Num();//返回数组元素
	int32 ArraySize2 = IntArray2.GetAllocatedSize();//计算元素大小
}

void AArrayActor::AddStructArray()
{
	StructArray.Add(150);
}

void AArrayActor::EmplaceStructArray()
{
	StructArray.Emplace(200);
}

TArray<FString> AArrayActor::AppendStrArray()//附加元素
{
	FString Arr[] = { TEXT("OF"),TEXT("Tomorow") };
	TArray<FString> StrArr;

	StrArr.Add("Hello");
	StrArr.Emplace(TEXT("World"));
	StrArr.Append(Arr, UE_ARRAY_COUNT(Arr));// UE_ARRAY_COUNT()  ->计入数组元素的个数

	return StrArr;
}

void AArrayActor::AddUniqueString()//向数组添加一个字符，如果出现重复就不添加.
{
	TArray<FString> StrArr = AppendStrArray();
	StrArr.AddUnique(TEXT("!"));
	StrArr.AddUnique(TEXT("!"));
}

TArray<FString> AArrayActor::InsertString()//插入元素
{
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","!" };
	StrArr.Insert(TEXT("Brave"), 1);
	return StrArr;
}

void AArrayActor::SetStringNum()//添加数组容量
{
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","!" };
	StrArr.SetNum(10);

	StrArr.SetNum(5);
}

void AArrayActor::AddUniqueStruct()//通过结构体判断元素内是否有相同的元素.
{
	TArray<FEqualStructInfo> EqualStructArray;
	EqualStructArray.AddUnique(0);
	EqualStructArray.AddUnique(1);
	EqualStructArray.AddUnique(1);
	EqualStructArray.AddUnique(2);
	EqualStructArray.AddUnique(3);

}

#pragma region ArrayRegion

void AArrayActor::LoopArray()//遍历数组的每一个元素
{
	FString JoinedStr;
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","	To","!" };
	for (const auto& Str : StrArr)
	{
		JoinedStr += Str;
		JoinedStr += TEXT("");
	}
}

void AArrayActor::LoopArray1()//通过下标遍历每个数组的元素
{
	FString JoinedStr1;
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","	To","!" };
	for (int32 Index = 0; Index != StrArr.Num(); ++Index)
	{
		JoinedStr1 += StrArr[Index];
		JoinedStr1 += TEXT("");
	}
}

void AArrayActor::LoopArray2()//通过迭代器遍历数组的每一个元素
{
	FString JoinedStr2;
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","	To","!" };
	for (auto It = StrArr.CreateConstIterator(); It; ++It)//CreateConstIterator()  -> 创建数组的迭代器，用于安全遍历数组，字符串拼接.
	{
		JoinedStr2 += *It;
		JoinedStr2 += TEXT("");
	}
}

void AArrayActor::LoopArray_Right()//从最后一个元素遍历数组
{
	FString JoinedStr3;
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","	To","!" };

	for (int32 Index = StrArr.Num() - 1; Index >= 0; --Index)
	{
		if (TEXT("OF") == StrArr[Index])
		{
			StrArr.RemoveAt(Index);
		}
		else
		{
			JoinedStr3 = StrArr[Index] + JoinedStr3;
			JoinedStr3 += TEXT("");
		}
	}
}

void AArrayActor::LoopArray_Right2()//遍历数组每一个元素并且移除指定的元素
{
	TArray<FString> StrArr = { "Hello","World","OF","Tomorow","	To","!" };
	TArray<int32>  RemoveIndexArray;

	for (int32 Index = StrArr.Num() - 1; Index >= 0; --Index)
	{
		if (TEXT("OF") == StrArr[Index])
		{
			RemoveIndexArray.Add(Index);
		}
	}

	//返回数组索引
	for (int32 RemovedLoopIndex = 0; RemovedLoopIndex != RemoveIndexArray.Num(); ++RemovedLoopIndex)
	{
		StrArr.RemoveAt(RemoveIndexArray[RemovedLoopIndex]);
	}
}

//匿名函数
void AArrayActor::TestLambda()
{
	int32 OriginNum = 100;
	auto Lambda = [OriginNum](int32 a, int32 b) ->int32 {
		int32 Max = a + b;

		Max += OriginNum;

		return Max;

		};

	int32 Calculate = Lambda(10, 20);
}

//数组的快排序
TArray<FString> AArrayActor::SortArray_Sort()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.Sort();
	return StrArr;
}

//数组的堆排序
TArray<FString> AArrayActor::SortArray_HeapSort()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.HeapSort();
	return StrArr;
}

//数组的归并排序
TArray<FString> AArrayActor::SortArray_StableSort()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.StableSort();
	return StrArr;
}

//二元谓词 -> 可以自定义比较数组元素，并且对它们进行排序.
TArray<FString> AArrayActor::SortArray_Sort_2()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.Sort([](const FString& A, const FString& B) {

		return A.Len() < B.Len();

	});

	return StrArr;
}

TArray<FString> AArrayActor::SortArray_HeapSort_2()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.HeapSort([](const FString& A, const FString& B) {

		return A.Len() < B.Len();

		});

	return StrArr;
}

TArray<FString> AArrayActor::SortArray_StableSort_2()
{
	TArray<FString> StrArr = { "aa","AA","AB","ABC","BB","VE","CCCC","AD","DDDDDA" };
	StrArr.StableSort([](const FString& A, const FString& B) {

		return A.Len() < B.Len();

		});

	return StrArr;
}

void AArrayActor::SortStructArray_StableSort()
{
	TArray<FSortStructInfo> MyTeams_01;
	MyTeams_01.Add({ 99,2 });
	MyTeams_01.Add({ 1,10 });
	MyTeams_01.Add({ 66,3 });
	MyTeams_01.Add({ 88,60 });

	TArray<FSortStructInfo> MyTeams_02;
	MyTeams_01.Add({ 99,2 });
	MyTeams_01.Add({ 1,10 });
	MyTeams_01.Add({ 66,3 });
	MyTeams_01.Add({ 88,60 });

	TArray<int32> LocalMyTeams;
	MyTeams_01.StableSort();
	MyTeams_02.StableSort([](const FSortStructInfo& X, const FSortStructInfo& Y) -> bool {

		return X.Money < Y.Money ? true : false;

		});
}

#pragma endregion ArrayRegion

#pragma region Find

  void AArrayActor::FindArray()
  {
	  //访问数组元素的内存!!!!
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  int32 ArrSize = StrArr.Num();

	  FString* StrPtr = StrArr.GetData();//动态数组，可以进行动态扩容.
	  bool bP0 = StrPtr[0] == "Hello";
	  bool bP1 = StrPtr[1] == "World";
	  bool bP2 = StrPtr[2] == "OF";
	  bool bP3 = StrPtr[3] == "Tomorow";
	  bool bP4 = StrPtr[4] == "To";
	  bool bP5 = *(StrPtr + 5) == "!";

	  FString MyTemp1 = *(StrPtr + 4);//FString MyTemp1 = "To"
	  FString MyTemp2 = *StrPtr + TEXT(" 4");//FString MyTemp2 = "Hello 4"
  }
   
  void AArrayActor::FindArray_Change()
  {
	  TArray<FString> StrArr1 = { "Hello","World","OF","Tomorow","To","!" };
	  TArray<FString> StrArr2 = { "1","2","3","4","5","6" };

	  //添加数组元素
	  StrArr1.Append(StrArr2);
	  StrArr1.Append(StrArr2);
	  StrArr1.Append(StrArr2);
	  StrArr1.Append(StrArr2);

	  FString* StrPtr = StrArr1.GetData();
	  bool bP0 = StrPtr[0] == "Hello";
	  bool bP1 = StrPtr[1] == "World";
	  bool bP2 = StrPtr[2] == "OF";
	  bool bP3 = StrPtr[3] == "Tomorow";
	  bool bP4 = StrPtr[4] == "To";
	  bool bP5 = *(StrPtr + 5) == "!";

	  bool bPz0 = StrArr1[0] == "Hello";
	  bool bPz1 = StrArr1[1] == "World";
	  bool bPz2 = StrArr1[2] == "OF";
	  bool bPz3 = StrArr1[3] == "Tomorow";
  }

  void AArrayActor::FindArray_Const()
  {
	  //容器为常量，返回的指针也为常量
	  const TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };
	  const FString* StrPtr = StrArr.GetData();
	  //*StrPtr = *StrPtr + TEXT("Test");
  }

  void AArrayActor::FindArray_ElementSize()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };
	  uint32 ElementSize1 = StrArr.GetTypeSize();//返回数组类型的字节大小
	  uint32 ElementSize2 = sizeof(FString);

	  TArray<int32> IntArr = { 1,2,3,4,5,6 };
	  uint32 ElementSize3 = IntArr.GetTypeSize();

	  TArray<uint8> Uint8Arr = { 1,2,3,4,5,6 };
	  uint32 ElementSize4 = Uint8Arr.GetTypeSize();
  }

  void AArrayActor::FindArray_Index()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  FString Elen1 = StrArr[1];//拷贝
	  Elen1 += TEXT("10"); //Elen1输出的值:" World10 "
	  
	  //别名引用
	  FString& Elen1_X = StrArr[1];//引用
	  Elen1_X += TEXT("10"); //Elen1_X输出的值:"Hello","World 10","OF","Tomorow","To","!" 
  }

  void AArrayActor::FindArray_IsValid()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  //判断是否越界访问
	  bool bValidM1 = StrArr.IsValidIndex(-1);
	  bool bValid0 = StrArr.IsValidIndex(0);
	  bool bValid1 = StrArr.IsValidIndex(1);
	  bool bValid2 = StrArr.IsValidIndex(2);
	  bool bValid3 = StrArr.IsValidIndex(3);
	  bool bValid4 = StrArr.IsValidIndex(4);
	  bool bValid5 = StrArr.IsValidIndex(5);
	  bool bValid6 = StrArr.IsValidIndex(6);
  }

  void AArrayActor::FindArray_Upper()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };
	  StrArr[1] = StrArr[1].ToUpper();//把数组里面的元素进行大写
  }

  void AArrayActor::FindArray_Latest()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  //访问数组末尾的元素
	  FString ElemEnd = StrArr.Last();
	  FString ElemEnd0 = StrArr.Last(0);
	  FString ElemEnd1 = StrArr.Last(1);
	  FString ElemTop = StrArr.Top();
  }

#pragma endregion Find

#pragma region Contain

  void AArrayActor::ContainArray()
  {
	  TArray<FString> StrArr = { "12347756","33","44" "Hello","World","OF","Tomorow","To","!" };

	  //检查数组是否包含指定元素?
	  bool bHello = StrArr.Contains(TEXT("Hello"));
	  bool bGoodbye = StrArr.Contains(TEXT("Goodbye"));

	  //自定义检查数组是否包含指定元素
	  int32 Find5Character = 0;
	  bool bLen5 = StrArr.ContainsByPredicate([&Find5Character](const FString& str) {

		  ++Find5Character;

		  UE_LOG(LogTemp, Warning, TEXT("bLen5,[%d]"), Find5Character);

			  return str.Len() == 5;
		   
		  });


	  int32 Find6Character = 0;
	  bool bLen6 = StrArr.ContainsByPredicate([&Find6Character](const FString& str) {

		  ++Find6Character;

		  UE_LOG(LogTemp, Warning, TEXT("bLen5,[%d]"), Find6Character);

			  return str.Len() == 6;

		  });

  }

  void AArrayActor::FindElementArray()
  {
	  //查找数组的元素并且返回元素的索引.
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  int32 Index = -1;
	  bool bIndex = StrArr.Find(TEXT("Hello"), Index);
	 
	  int32 LastIndex = -1;
	  bool bIndexFromLast = StrArr.FindLast(TEXT("World"), LastIndex);

	  int32 ErrIndex = -1;
	  bool bErrIndex = StrArr.Find(TEXT("666"), ErrIndex);


	  int32 Index2 = StrArr.Find(TEXT("OF"));

	  int32 IndexLast2 = StrArr.FindLast(TEXT("Tomorow"));

	  int32 ErrIndex2 = StrArr.Find(TEXT("2333"));

	  bool IndexNone = INDEX_NONE == ErrIndex2;

  }

  void AArrayActor::FindElementByKey()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  //通过值查找索引
	  int32 Index = StrArr.IndexOfByKey(TEXT("Hello"));

	  //在数组中查找带有 "r" 值，并将它的索引返回给用户.
	  int32 IndexP = StrArr.IndexOfByPredicate([](const FString& str) {

		  return str.Contains(TEXT("r"));

		  });

	  TArray<FFindStructInfo> StructArr;

	  //添加元素
	  StructArr.Add(FFindStructInfo(1, 20));
	  StructArr.Add(FFindStructInfo(2, 30));
	  StructArr.Add(FFindStructInfo(4, 50));

	  //查找ID是否为4
	  bool bFind = StructArr[1] == 2;
	  int32 IndexStuctP = StructArr.IndexOfByKey(4);

	  //测试代码
	  int32 a = 1;
  }

  void AArrayActor::FindElementRetPtr()
  {
	  TArray<FString> StrArr = { "Hello","World","OF","Tomorow","To","!" };

	  //auto*:自动推断一级指针类型.
	  auto* OfPtr = StrArr.FindByKey(TEXT("OF"));
	  auto* ThePtr = StrArr.FindByKey(TEXT("the"));

	  FString* RealOfPtr = StrArr.FindByKey(TEXT("OF"));
	  FString* RealThePtr = StrArr.FindByKey(TEXT("the"));
	  if (RealOfPtr)
	  {
		  (*RealOfPtr) += TEXT("Modify");
	  }

	  //元素类型指针
	  //在Actor数组中查找自己，并且将自己的位置重置到原点
	  TArray<AActor*> MyActors = { this,nullptr,nullptr };
	  auto* ThisActor1 = MyActors.FindByKey(this);
	  AActor** ThisActor2 = MyActors.FindByKey(this);
	  if (AActor** ThisActor3 = MyActors.FindByKey(this))
	  {
		  (*ThisActor3)->SetActorLocation(FVector::ZeroVector);
	  }

	  //按长度查找数组元素
	  auto* Len5Ptr = StrArr.FindByPredicate([](const FString& str) {

		  return str.Len() == 5;

		  });

	  auto* Len6Ptr = StrArr.FindByPredicate([](const FString& str) {

		  return str.Len() == 6;

		  });

	  //遍历数组，把不为空且字母小于‘M’的字符串挑出来，放入到数组中
	  auto Filte = StrArr.FindByPredicate([](const FString& str) {

		  return !str.IsEmpty() && str[0] < TEXT('M');

		  });

	  int32 a = 1;
  }

#pragma endregion Contain

#pragma region Remove

  void AArrayActor::RemoveElement()
  {
	  TArray<int32> ValArr;

	  int32 Temp[] = { 10,20,30,5,10,15,20,25,30 };

	  ValArr.Append(Temp, 9);

	  ValArr.Remove(20);

	  //移除相同的元素的第一个元素，比如（2 ,1，2） 移除->  (被移除 ,1 , 2)
	  ValArr.RemoveSingle(30);

	  //按照索引进行移除
	  if (ValArr.IsValidIndex(2))
	  {
		  ValArr.RemoveAt(2);
	  }
	  
	  ValArr.Shrink();//申请一块新的内存空间

	  if (ValArr.IsValidIndex(99))
	  {
		  ValArr.RemoveAt(99);
	  }
  }

  void AArrayActor::RemoveMultiElement()
  {
	  TArray<int32> ValArr;

	  int32 Temp[] = { 1,2,3,4,1,2,3,4,5 };

	  ValArr.Append(Temp, 9);

	  ValArr.RemoveAll([](int32 val) {

		  return val % 3 == 0;

		  });

	  //在数组中寻找为2的进行移除
	  ValArr.Empty();//移除所有元素
	  ValArr.Append(Temp, 9);
	  ValArr.RemoveSwap(2);

	  //在数组中按索引交换移除
	  ValArr.Empty();
	  ValArr.Append(Temp, 9);
	  ValArr.RemoveAtSwap(0);

	  //在数组中按条件交换移除
	  ValArr.Empty(10);//始终保持大小为10
	  ValArr.Append(Temp, 9);
	  ValArr.RemoveAllSwap([](int32 val) {

		  return val % 3 == 0;

		  });
  }

  void AArrayActor::OperateArray()
  {
	  TArray<int32> ValArr1;
	  ValArr1.Add(1);
	  ValArr1.Add(2);
	  ValArr1.Add(3);

	  auto ValArr2 = ValArr1;
	  TArray<int32> ValArr3 = ValArr1;
	  ValArr2[0] = 5;

	  TArray<int32> ValArr4;
	  ValArr4 += ValArr2;
	  ValArr4.Append(ValArr1);

	  //把原数组的元素放在新数组里面.(这是深拷贝)
	  TArray<int32> ValArr5 = { 1,1,1 };
	  ValArr5 = MoveTemp(ValArr4);

  }

  void AArrayActor::OperateStrArray()
  {
	  TArray<FString> FlavorArr1;
	  FlavorArr1.Emplace(TEXT("Chocolate"));
	  FlavorArr1.Emplace(TEXT("Vanilla"));

	  auto FlavorArr2 = FlavorArr1;

	  bool bComparison1 = FlavorArr1 == FlavorArr2;

	  for (auto& str : FlavorArr2)
	  {
		  str = str.ToUpper();
	  }

	  bool bComparison2 = FlavorArr1 == FlavorArr2;

	  //交换数组中的两个元素(引用交换)
	  Exchange(FlavorArr2[0], FlavorArr2[1]);

	  bool bComparison3 = FlavorArr1 == FlavorArr2;

  }

#pragma endregion Remove

#pragma region  Heapon

  void AArrayActor::HeaponArray()
  {
	  TArray<int32> HeapArr;
	  for (int32 val = 10; val != 0; --val)
	  {
		  HeapArr.Add(val);
	  }

	  //对数组堆排序
	  HeapArr.Heapify();

	  //在堆元素中一个新的元素
	  HeapArr.HeapPush(4);

	  //从堆中移除顶部元素
	  int32 TopHeap;
	  HeapArr.HeapPop(TopHeap);

	  //检查堆的顶部节点，无需变更数组
	  int32 Top = HeapArr.HeapTop();
  }

#pragma endregion  Heapon
 
#pragma region  Slack

  void AArrayActor::SlackArray()
  {
	  TArray<int32> SlackArr;

	  //SlackArr.GetSlack() -> 在数组中空着没有用的位置，有几个,如果满了则自动扩容.
	  int32 SlackNum = SlackArr.GetSlack();
	  int32 Num = SlackArr.Num();
	  int32 Max = SlackArr.Max();

	  SlackArr.Add(1);

	  SlackNum = SlackArr.GetSlack();
	  Num = SlackArr.Num();
	  Max = SlackArr.Max();
	  
	  SlackArr.Add(2);
	  SlackArr.Add(3);
	  SlackArr.Add(4);
	  SlackArr.Add(5);

	  SlackNum = SlackArr.GetSlack();
	  Num = SlackArr.Num();
	  Max = SlackArr.Max();
  }

  void AArrayActor::SlackArray_Empty()
  {
	  TArray<int32> SlackArr;

	  SlackArr.Add(10);
	  SlackArr.Add(11);
	  SlackArr.Empty();

	  SlackArr.Add(2);
	  SlackArr.Add(3);
	  SlackArr.Empty(3);//设置最大容量为三

	  SlackArr.Add(1);
	  SlackArr.Add(2);
	  SlackArr.Add(3);
	  SlackArr.Add(4);
  }

  void AArrayActor::SlackArray_Reset()
  {
	  TArray<int32> SlackArr;

	  SlackArr.Add(1);
	  SlackArr.Add(2);
	  SlackArr.Add(3);

	  //SlackArr.Reset() -> 清空数组元素，但是不会改变内存分配.
	  SlackArr.Reset(0);
	  SlackArr.Reset(10);
  }

  void AArrayActor::ShrinkArray()
  {
	  TArray<int32> SlackArr;

	  SlackArr.Add(1);
	  SlackArr.Add(2);
	  SlackArr.Add(3);

	  //将数组的元素清空，并将已用内存缩小到当前元素所需的最小大小
	  SlackArr.Shrink();
  }

#pragma endregion  Slack

#pragma region Origin

  void AArrayActor::OriginArray()
  {
	  int32 SrcInts[] = { 2,3,4,7,8 };

	  //在初始化前，添加五个未初始化的元素
	  TArray<int32> UninitInts;
	  UninitInts.AddUninitialized(5);

	  FMemory::Memcpy(UninitInts.GetData(), SrcInts, 8 * sizeof(int32));

  }

  void AArrayActor::OriginStringArray()
  {
	  TArray<FString> UninitStrs;

	  UninitStrs.Emplace(TEXT("A"));
	  UninitStrs.Emplace(TEXT("D"));

	  //在初始化前，在指定的数组下标插入未初始化的元素
	  UninitStrs.InsertUninitialized(1, 2);
	  new (UninitStrs.GetData() + 1) FString(TEXT("B"));
	  new (UninitStrs.GetData() + 2) FString(TEXT("C"));
  }

  void AArrayActor::ZeroArray()
  {
	  //在数组末尾添加新元素(不会调用构造函数)
	  TArray<FAddStructInfo> UninitStructs;
	  UninitStructs.AddZeroed();
	  UninitStructs.Empty();
  }

  void AArrayActor::ZeroAndUninitArray()
  {
	  //缩小数组容量的大小
	  TArray<FAddStructInfo> UninitStructs;
	  UninitStructs.AddZeroed();
	  UninitStructs.SetNumUninitialized(10);
	  new (UninitStructs.GetData() + 1) FString(TEXT("A"));
	  new (UninitStructs.GetData() + 2) FString(TEXT("B"));
	  UninitStructs.SetNumZeroed(5);
	  UninitStructs.SetNumZeroed(2);
  }

#pragma endregion  Origin

#pragma region  Other

  void AArrayActor::SwapArray()
  {
	  TArray<int32> MyInts = { 1,2,3,4,5 };

	  //Swap与SwapMemory的区别:一个是交换元素的值，另一个是交换元素的内存地址.
	  MyInts.Swap(1, 2);
	  MyInts.SwapMemory(0, 4);
  }

  void AArrayActor::AddDefaultArray()
  {
	  TArray<FAddStructInfo> MyInts = { 100,200,300,400,500 };

	  // 在队伍最后塞一个“默认白板”，只发一张“座位号”（索引）
      // 注意：它是在最后加新人，绝对不是把第一个人复制过来！
	  int32 DefaultAddIndex = MyInts.AddDefaulted(); 

	  // 在队伍最后塞一个“默认白板”，直接把“本人”（引用）拽到我面前
      // 注意：因为拿到了引用，我们可以当场直接修改他的属性（效率更高）
	  FAddStructInfo& LastMyStruct = MyInts.AddDefaulted_GetRef();
	  LastMyStruct.Healty += 100;
  }

  void AArrayActor::ReserveArray()
  {
	  //根据给定的数字来取最大值进行扩容.
	  TArray<int32> MyInts;
	  MyInts.Reserve(3);
	  MyInts.Add(1);
	  MyInts.Add(2);
	  MyInts.Add(3);
	  MyInts.Reserve(5);
	  MyInts.Reserve(2);
  }

#pragma endregion  Other

  

  // Called when the game starts or when spawned
void AArrayActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArrayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

