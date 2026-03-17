// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FCombatState.h"
#include "Interface/IHolderAttribute.h"

FCombatState::FCombatState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, const ECombatState InputState)
	: BaseState(InHolderA, InHolderF)
{
	CurrentState = InputState;
}

FCombatState::~FCombatState()
{
}

void FCombatState::OnEnter()
{
	float Value = 0;
	switch (CurrentState)
	{
	case ECombatState::Idle:

		break;
	case ECombatState::Combat:
		Value = 1;
		break;
	}
	InHolderFunction->SwitchCombatAnimation_Implementation(Value);
}

void FCombatState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case ECombatState::Idle:
		break;
	case ECombatState::Combat:
		break;
	}
}

void FCombatState::OnExit()
{
	switch (CurrentState)
	{
	case ECombatState::Idle:
		break;
	case ECombatState::Combat:
		break;
	}
}
