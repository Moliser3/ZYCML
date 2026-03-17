// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FTopState.h"

#include "Interface/IHolderAttribute.h"

FTopState::FTopState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, const ETopState InputState) : BaseState(InHolderA, InHolderF)
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
		//UE_LOG(LogTemp, Log, TEXT("获得新生"));
		break;
	case ETopState::Dead:
		//UE_LOG(LogTemp, Log, TEXT("获得死亡"));
		break;
	}
}

void FTopState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case ETopState::Living:
		//UE_LOG(LogTemp, Log, TEXT("新生ing"));
		if (InHolderAttribute->GetHealth_Implementation() <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("切换状态 -> TopState::Dead"));
			InHolderFunction->SwitchTopState_Implementation(ETopState::Dead);
		}

		break;
	case ETopState::Dead:
		//UE_LOG(LogTemp, Log, TEXT("死亡ing"));
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
