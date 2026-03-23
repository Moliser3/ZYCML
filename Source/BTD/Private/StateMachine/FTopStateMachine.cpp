// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FTopStateMachine.h"

#include "Interface/IHolderFunction.h"
#include "StateMachine/FTopState.h"

FTopStateMachine::FTopStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF) : BaseStateMachine(InHolderA, InHolderF)
{
}

FTopStateMachine::~FTopStateMachine()
{
}
