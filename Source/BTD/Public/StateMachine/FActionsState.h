// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

/**
 * 行为状态节点，对应 ECharacterBehavior 枚举
 */
class BTD_API FActionsState : public BaseState
{
public:
	explicit FActionsState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD,IIHolderStateMachine*	InHolderM,const ECharacterBehavior InputState);

	virtual ~FActionsState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	ECharacterBehavior CurrentState;
};
