// Fill out your copyright notice in the Description page of Project Settings.


#include "YXFPSGameMode.h"

void AYXFPSGameMode::StartPlay()
{
	Super::StartPlay();

	// check 是虚幻引擎的断言宏。如果 GEngine 为空（nullptr），程序会在这里报错崩溃并弹窗
   //  作用：防止后续使用 GEngine 时出现空指针引用（野指针）导致更严重的闪退
	check(GEngine != nullptr);
	
    // 在游戏屏幕上打印一条调试信息
    // 参数解析：
    // GEngine：全局引擎指针
    // AddOnScreenDebugMessage：在屏幕上添加调试信息的函数
    // -1：键值（Key）。填 -1 表示每次调用都新增一条消息，不会覆盖之前的；填正数则相同键值的消息会覆盖更新
    // 5.0f：显示时长，单位为秒（5秒后消失）
    // FColor::Yellow：文字颜色设为黄色
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World , this is FPSGameMode!"));
}