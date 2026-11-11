// Fill out your copyright notice in the Description page of Project Settings.


#include "YXCameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AYXCameraDirector::AYXCameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYXCameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYXCameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 定义常量：设定摄像机切换的间隔时间为 2.0 秒
    const float TimeBetWeenCameraChanges = 2.0f;

    // 定义常量：设定平滑过渡（运镜）的时间为 0.75 秒
    const float SmoothBlendTime = 0.75f;

    // 【倒计时逻辑】每一帧都在减去 DeltaTime（上一帧到这一帧流逝的时间），相当于计时器在走
    TimeToNexCameraChange -= DeltaTime;

    // 如果倒计时归零或小于0，说明 2 秒钟到了，该切换摄像机了
    if (TimeToNexCameraChange <= 0)
    {
        // 重置倒计时。
        // 注意：这里用 += 而不是 =，是为了防止游戏卡顿（掉帧）时，时间重置不准确。
        TimeToNexCameraChange += TimeBetWeenCameraChanges;

        // 查找处理本地玩家控制器的Actor。（0 代表玩家0号，即你本人）
        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

        // 安全检查：确保我们成功拿到了玩家控制器，防止后面的代码报错导致游戏崩溃
        if (OurPlayerController)
        {
            // 判断1：现在的镜头是不是 CameraOne？
            // 判断2：CameraOne 是不是空指针？（即确保场景里真的有这个摄像机，没被删掉）
            if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
            {
                // 如果条件满足，执行：立即切换摄像机1
                // SetViewTarget 是“瞬间切换”，玩家眼前画面会直接闪过去
                OurPlayerController->SetViewTarget(CameraOne);
            }
            // 如果当前镜头不是 CameraOne，就检查是不是该切到 CameraTwo 了
            else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
            {
                // 如果条件满足，执行：平滑混合到摄像机2
                // SetViewTargetWithBlend 是“平滑过渡”，会带有一个 0.75秒的运镜动画
                OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
            }
        }
    }
}

