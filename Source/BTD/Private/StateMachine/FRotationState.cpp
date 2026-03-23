// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FRotationState.h"
#include "Interface/IHolderAttribute.h"

FRotationState::FRotationState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD,IIHolderStateMachine*	InHolderM, const EActorRotaType InputState)
	: BaseState(InHolderA, InHolderF, InHolderD,InHolderM)
{
	CurrentState = InputState;
}

FRotationState::~FRotationState()
{
}

void FRotationState::OnEnter()
{
	switch (CurrentState)
	{
	case EActorRotaType::Rotating:
		break;
	case EActorRotaType::Gazing:
		break;
	}
}

void FRotationState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case EActorRotaType::Rotating:
		break;
	case EActorRotaType::Gazing:
		break;
	}
}

void FRotationState::OnExit()
{
	switch (CurrentState)
	{
	case EActorRotaType::Rotating:
		break;
	case EActorRotaType::Gazing:
		break;
	}
}
