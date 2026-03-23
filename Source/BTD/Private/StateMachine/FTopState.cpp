// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FTopState.h"

#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderData.h"
#include "Interface/IHolderStateMachine.h"

FTopState::FTopState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const ETopState InputState) : BaseState(
	InHolderA, InHolderF, InHolderD, InHolderM)
{
	CurrentState = InputState;
}

FTopState::~FTopState()
{
}

void FTopState::OnEnter()
{
	switch (CurrentState)
	{
	case ETopState::Living:
		break;
	case ETopState::Dead:
		break;
	}
}

void FTopState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case ETopState::Living:

		if (InHolderData->GetHealth() <= 0)
		{
			InHolderStateMachine->SwitchTopState(ETopState::Dead);
		}
		break;
	case ETopState::Dead:
		break;
	}
}

void FTopState::OnExit()
{
	switch (CurrentState)
	{
	case ETopState::Living:
		UE_LOG(LogTemp, Log, TEXT("退出新生"));
		break;
	case ETopState::Dead:
		UE_LOG(LogTemp, Log, TEXT("退出死亡"));
		break;
	}
}
