// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Interface/IHolderFunction.h"

enum class ETopState : uint8;
/**
 * 
 */
class BTD_API FTopState : public BaseState
{
public:
	explicit FTopState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const ETopState InputState);

	virtual ~FTopState() override;
	virtual void OnEnter() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnExit() override;

	ETopState CurrentState;
};
