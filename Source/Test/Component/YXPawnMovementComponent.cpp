// Fill out your copyright notice in the Description page of Project Settings.


#include "YXPawnMovementComponent.h"

void UYXPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//必须调用父类的TickComponent
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//安全检查：没有主人、没有目标、不需要更新，跳过这一帧
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//计算这一帧角色应该移动多远、往哪个方向移动(方向 × 速度 × 时间)
	//1. ConsumeInputVector() ->获取并清空输入。
	//2. GetClampedToMaxSize(1.0f) ->限制最大长度（防作弊）.
	//意思是将向量变成长度为 1 的方向向量（如果是零向量就不会崩）
	//GetSafeNormal()-> 防止斜向加速
	//FVector DesiredMovementThisFrame = ConsumeInputVector().GetSafeNormal() * DeltaTime * 150.0f;
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;

	//如果算出来的位移不是0（说明玩家按了方向键），就执行移动
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		// 用来存放碰撞结果（比如撞墙了没）
		FHitResult Hit;
		
		//通知组件真正移动，引擎会自动处理碰撞、滑动等物理效果
		//SafeMoveUpdatedComponent() -> 它负责让你绑定的组件（比如角色的胶囊体）安全地移动，
		           //并且在移动过程中帮你自动处理“撞墙”、“卡死”、“穿模”等物理碰撞问题
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//如果撞墙了（Hit 有阻挡），沿着墙边滑行（防止卡墙）
		//IsValidBlockingHit()：判断刚才移动时是不是真的撞到了“实体墙”（而不是树叶、空气墙等不阻挡的物体）
		if (Hit.IsValidBlockingHit())
		{
			//SlideAlongSurface：它会自动利用你撞墙的剩余时间和墙面法线（Hit.Normal），把剩余位移投影到墙面上，让角色沿着墙边滑行过去
			//f - Hit.Time 算的是撞墙后还剩多少“移动时间/距离”没用完
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}