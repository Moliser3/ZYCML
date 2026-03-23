// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseState.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderFunction.h"
#include "Interface/IHolderData.h"

BaseState::BaseState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM) : InHolderAttribute(InHolderA),
	InHolderFunction(InHolderF), InHolderData(InHolderD), InHolderStateMachine(InHolderM)
{
}

BaseState::~BaseState()
{
}
