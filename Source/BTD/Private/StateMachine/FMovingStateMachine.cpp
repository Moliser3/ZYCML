// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FMovingStateMachine.h"
#include "Interface/IHolderFunction.h"

FMovingStateMachine::FMovingStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF)
	: BaseStateMachine(InHolderA, InHolderF)
{
}

FMovingStateMachine::~FMovingStateMachine()
{
}
