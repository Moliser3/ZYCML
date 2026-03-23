// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FMovingState.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderData.h"

FMovingState::FMovingState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const EMoveState InputState)
	: BaseState(InHolderA, InHolderF, InHolderD, InHolderM)
{
	CurrentState = InputState;
}

FMovingState::~FMovingState()
{
}

void FMovingState::OnEnter()
{
	switch (CurrentState)
	{
	case EMoveState::Walking:
		break;
	case EMoveState::Running:
		break;
	}
}

void FMovingState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case EMoveState::Walking:
		InHolderFunction->SetMovementSpeed_Implementation(InHolderData->GetWalkSpeed());
		break;
	case EMoveState::Running:
		InHolderFunction->SetMovementSpeed_Implementation(InHolderData->GetRunSpeed());
		break;
	}
}

void FMovingState::OnExit()
{
	switch (CurrentState)
	{
	case EMoveState::Walking:
		break;
	case EMoveState::Running:
		break;
	}
}
