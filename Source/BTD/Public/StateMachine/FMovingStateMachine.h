// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

/**
 * 移动状态机
 */
class BTD_API FMovingStateMachine : public BaseStateMachine
{
public:
	explicit FMovingStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~FMovingStateMachine();
};
