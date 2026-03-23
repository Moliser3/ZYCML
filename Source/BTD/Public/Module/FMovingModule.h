// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderStateMachine.h"

/**
 * 
 */
class BTD_API FMovingModule
{
public:
	explicit FMovingModule(IIHolderAttribute* InHolderA, IIHolderStateMachine* InHolderM);
	~FMovingModule();
	void MovingModuleTick(float DeltaTime);

private:
	IIHolderAttribute* HolderAttribute;
	IIHolderStateMachine* HolderStateMachine;
	// 移动状态检查计时器
	float MoveStateCheckTimer;
	// 移动状态检查的时间间隔（秒）
	float MoveStateCheckInterval;
	// 上一次位置
	FVector LastRecordedPosition;
};
