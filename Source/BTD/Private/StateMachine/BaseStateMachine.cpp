// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseStateMachine.h"
#include "Interface/IState.h"

BaseStateMachine::BaseStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF) : InHolderAttribute(InHolderA), InHolderFunction(InHolderF), CurrentState(nullptr)
{
}

BaseStateMachine::~BaseStateMachine()
{
	if (CurrentState)
	{
		CurrentState->OnExit();
		delete CurrentState;
		CurrentState = nullptr;
	}
}

void BaseStateMachine::Transition(IState* NewState)
{
	if (CurrentState)
	{
		CurrentState->OnExit();
		delete CurrentState;
		CurrentState = nullptr;
	}
	CurrentState = NewState;
	CurrentState->OnEnter();
}

void BaseStateMachine::Update(const float DeltaTime) const
{
	if (!CurrentState)
		return;
	CurrentState->OnUpdate(DeltaTime);
}
