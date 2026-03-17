// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IState.h"
class IIHolderFunction;
class IIHolderAttribute;
/**
 * 
 */
class BTD_API BaseState : public IState
{
public:
	explicit BaseState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	virtual ~BaseState() override;

protected:
	IIHolderAttribute* InHolderAttribute;
	IIHolderFunction* InHolderFunction;
};
