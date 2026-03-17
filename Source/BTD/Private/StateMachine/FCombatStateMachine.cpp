// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FCombatStateMachine.h"
#include "Interface/IHolderFunction.h"

FCombatStateMachine::FCombatStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF)
	: BaseStateMachine(InHolderA, InHolderF)
{
}

FCombatStateMachine::~FCombatStateMachine()
{
}
