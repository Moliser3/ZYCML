// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Interface/IState.h"
class IIHolderStateMachine;
class IIHolderFunction;
class IIHolderAttribute;
class IIHolderData;
/**
 *
 */
class BTD_API BaseState : public IState
{
public:
	explicit BaseState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD,IIHolderStateMachine* InHolderM);
	virtual ~BaseState() override;

protected:
	IIHolderAttribute* InHolderAttribute;
	IIHolderFunction* InHolderFunction;
	IIHolderData* InHolderData;
	IIHolderStateMachine* InHolderStateMachine;
};
