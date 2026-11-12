// Fill out your copyright notice in the Description page of Project Settings.


#include "YXCameraDirectorModify.h"
#include "Kismet/GameplayStatics.h" // 包含静态函数库（用来找玩家、找Actor）
#include "Camera/CameraActor.h"     // 包含摄像机类（用来在场景里筛选摄像机）

// Sets default values
AYXCameraDirectorModify::AYXCameraDirectorModify()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYXCameraDirectorModify::BeginPlay()
{
	Super::BeginPlay();

    // 准备一个Actor类型的数组，用来装找出来的摄像机。
	TArray<AActor*> MyCameraActors;

    // 让引擎帮我们在整个场景里，把所有的“摄像机(CameraActor)”都找出来，放入到数组里面。
	UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), MyCameraActors);

    // 清空数组的元素，防止之前有残留数据。
	CameraInfoList.Empty();

    //注意: check() 相当于断言。如果场景里的摄像机数量不多于1个（比如0个或1个），游戏直接崩溃报错！
	check(MyCameraActors.Num() > 1);

   // 遍历找到的每一个摄像机
	for (int32 Index = 0; Index < MyCameraActors.Num(); Index++)
	{
        // AddDefaulted_GetRef()：在数组末尾新建一个空的结构体，并拿到它的“引用”（直接操作它）
		FToggleCameraInfo& CameraInfo = CameraInfoList.AddDefaulted_GetRef();

        // 把找到的摄像机赋给结构体里的变量。
		CameraInfo.CameraOne = MyCameraActors[Index];

        // 动态计算过渡时间：基础时间是1.0秒，然后根据索引增加。
		CameraInfo.CameraBlendTime += Index / 4.f;
	}

    // 初始化索引为0
    CameraIndex = 0;
}

// Called every frame
void AYXCameraDirectorModify::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 设定每 2 秒切换一次
    const float TimeBetWeenCameraChanges = 2.0f;

    // 倒计时不断减少
    TimeToNexCameraChange -= DeltaTime;

    // 时间到了
    if (TimeToNexCameraChange <= 0.0f)
    {
        // 重置倒计时，开始下一轮
        TimeToNexCameraChange += TimeBetWeenCameraChanges;

        // 索引 +1，准备切下一个
        CameraIndex++;

        // 如果索引超出了数组的长度，就绕回到第0个（实现循环播放）。
        if (CameraIndex > CameraInfoList.Num() - 1)
        {
            CameraIndex = 0;
        }

        // 获取玩家控制器
        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

        // 根据索引拿到“下一个摄像机”和它的“专属平滑时间”。
        AActor* NextCamera = CameraInfoList[CameraIndex].CameraOne;
        float NextBlendTime = CameraInfoList[CameraIndex].CameraBlendTime;

        // 如果有控制器，且下一个摄像机不是空的，就执行平滑切换。
        if (OurPlayerController && NextCamera)
        {
            OurPlayerController->SetViewTargetWithBlend(NextCamera, NextBlendTime);
        }
    }
}

