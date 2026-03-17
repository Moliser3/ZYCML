// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FMovingState.h"
#include "Interface/IHolderAttribute.h"

FMovingState::FMovingState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, const EMoveState InputState)
	: BaseState(InHolderA, InHolderF)
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
		break;
	case EMoveState::Running:
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
