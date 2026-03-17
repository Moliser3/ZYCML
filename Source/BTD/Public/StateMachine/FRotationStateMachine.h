// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

/**
 * 旋转状态机
 */
class BTD_API FRotationStateMachine : public BaseStateMachine
{
public:
	explicit FRotationStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~FRotationStateMachine();
};
