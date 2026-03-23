// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

/**
 * 旋转状态节点，对应 EActorRotaType 枚举
 */
class BTD_API FRotationState : public BaseState
{
public:
	explicit FRotationState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const EActorRotaType InputState);

	virtual ~FRotationState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	EActorRotaType CurrentState;
};
