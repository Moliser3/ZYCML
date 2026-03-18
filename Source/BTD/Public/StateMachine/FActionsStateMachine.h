// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

enum class ECharacterBehavior : uint8;
/**
 * 行为状态机
 */
class BTD_API FActionsStateMachine : public BaseStateMachine
{
public:
	explicit FActionsStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~FActionsStateMachine();
};
