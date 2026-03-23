// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FActionsState.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderData.h"

FActionsState::FActionsState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM,
                             const ECharacterBehavior InputState): BaseState(InHolderA, InHolderF, InHolderD, InHolderM)
{
	CurrentState = InputState;
}

FActionsState::~FActionsState()
{
}

void FActionsState::OnEnter()
{
	switch (CurrentState)
	{
	case ECharacterBehavior::Idle:
		break;
	case ECharacterBehavior::Moving:
		break;
	case ECharacterBehavior::Death:
		break;
	case ECharacterBehavior::Jump:
		break;
	case ECharacterBehavior::Hit:
		break;
	case ECharacterBehavior::Defense:
		break;
	case ECharacterBehavior::Attack:
		break;
	}
}

void FActionsState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case ECharacterBehavior::Idle:
		break;
	case ECharacterBehavior::Moving:
		break;
	case ECharacterBehavior::Death:
		break;
	case ECharacterBehavior::Jump:
		break;
	case ECharacterBehavior::Hit:
		break;
	case ECharacterBehavior::Defense:
		break;
	case ECharacterBehavior::Attack:
		break;
	}
}

void FActionsState::OnExit()
{
	switch (CurrentState)
	{
	case ECharacterBehavior::Idle:
		break;
	case ECharacterBehavior::Moving:
		break;
	case ECharacterBehavior::Death:
		break;
	case ECharacterBehavior::Jump:
		break;
	case ECharacterBehavior::Hit:
		break;
	case ECharacterBehavior::Defense:
		break;
	case ECharacterBehavior::Attack:
		break;
	}
}
