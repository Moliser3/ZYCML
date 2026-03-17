// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

/**
 * 武器状态机
 */
class BTD_API FWeaponStateMachine : public BaseStateMachine
{
public:
	explicit FWeaponStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~FWeaponStateMachine();
};
