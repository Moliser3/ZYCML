// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEnums.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderStateMachine.h"

// 注视状态下移动方向改变委托
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGazingMoveDirectionChanged, EMoveDirection);

/**
 *
 */
class BTD_API FMovingModule
{
public:
	explicit FMovingModule(IIHolderAttribute* InHolderA, IIHolderStateMachine* InHolderM);
	~FMovingModule();
	void MovingModuleTick(float DeltaTime);
	EMoveDirection GetMoveDirection() const { return CurrentMoveDirection; }

	// 注册注视移动方向改变事件
	FDelegateHandle RegisterMoveDirectionChanged(const FOnGazingMoveDirectionChanged::FDelegate& Delegate);
	// 注销注视移动方向改变事件
	void UnregisterMoveDirectionChanged(FDelegateHandle Handle);

private:
	// 注视状态下移动方向改变委托
	FOnGazingMoveDirectionChanged OnGazingMoveDirectionChanged;

	IIHolderAttribute* HolderAttribute;
	IIHolderStateMachine* HolderStateMachine;
	// 移动状态检查计时器
	float MoveStateCheckTimer;
	// 移动状态检查的时间间隔（秒）
	float MoveStateCheckInterval;
	// 上一次位置
	FVector LastRecordedPosition;
	// 当前移动方向
	EMoveDirection CurrentMoveDirection;
};
