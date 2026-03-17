// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FActionsStateMachine.h"
#include "Interface/IHolderFunction.h"

FActionsStateMachine::FActionsStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF)
	: BaseStateMachine(InHolderA, InHolderF)
{
}

FActionsStateMachine::~FActionsStateMachine()
{
}
