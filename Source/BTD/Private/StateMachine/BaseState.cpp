// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseState.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderFunction.h"

BaseState::BaseState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF) : InHolderAttribute(InHolderA), InHolderFunction(InHolderF)
{
}

BaseState::~BaseState()
{
}
