// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

/**
 * 移动状态节点，对应 EMoveState 枚举
 */
class BTD_API FMovingState : public BaseState
{
public:
	explicit FMovingState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, const EMoveState InputState);

	virtual ~FMovingState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	EMoveState CurrentState;
};
