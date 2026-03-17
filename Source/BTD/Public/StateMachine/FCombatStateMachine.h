// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

/**
 * 角色状态状态机
 */
class BTD_API FCombatStateMachine : public BaseStateMachine
{
public:
	explicit FCombatStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~FCombatStateMachine();
};
