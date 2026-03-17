// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

/**
 * 武器状态节点，对应 ECombatType 枚举
 */
class BTD_API FWeaponState : public BaseState
{
public:
	explicit FWeaponState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, const ECombatType InputState);

	virtual ~FWeaponState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	ECombatType CurrentState;
};
