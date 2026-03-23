// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FCombatState.h"
#include "Interface/IHolderAttribute.h"

FCombatState::FCombatState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const ECombatState InputState)
	: BaseState(InHolderA, InHolderF, InHolderD, InHolderM)
{
	CurrentState = InputState;
}

FCombatState::~FCombatState()
{
}

void FCombatState::OnEnter()
{
	switch (CurrentState)
	{
	case ECombatState::Idle:
		break;
	case ECombatState::Combat:
		break;
	}
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
