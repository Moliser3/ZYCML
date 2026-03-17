// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateMachine.h"

/**
 * 
 */
class BTD_API FTopStateMachine : public BaseStateMachine
{
public:
   explicit FTopStateMachine(IIHolderAttribute* InHolderA,IIHolderFunction* InHolderF);
    ~FTopStateMachine();
};