// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

/**
 * 角色状态节点，对应 ECombatState 枚举
 */
class BTD_API FCombatState : public BaseState
{
public:
	explicit FCombatState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const ECombatState InputState);

	virtual ~FCombatState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	ECombatState CurrentState;
};
