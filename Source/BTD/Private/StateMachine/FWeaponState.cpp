// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FWeaponState.h"
#include "Interface/IHolderAttribute.h"

FWeaponState::FWeaponState(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD, IIHolderStateMachine* InHolderM, const ECombatType InputState)
	: BaseState(InHolderA, InHolderF, InHolderD, InHolderM)
{
	CurrentState = InputState;
}

FWeaponState::~FWeaponState()
{
}

void FWeaponState::OnEnter()
{
	switch (CurrentState)
	{
	case ECombatType::Boxing:
		break;
	case ECombatType::OneHandedSword:
		break;
	case ECombatType::OneHandedSaber:
		break;
	case ECombatType::LongStaff:
		break;
	}
}

void FWeaponState::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case ECombatType::Boxing:
		break;
	case ECombatType::OneHandedSword:
		break;
	case ECombatType::OneHandedSaber:
		break;
	case ECombatType::LongStaff:
		break;
	}
}

void FWeaponState::OnExit()
{
	switch (CurrentState)
	{
	case ECombatType::Boxing:
		break;
	case ECombatType::OneHandedSword:
		break;
	case ECombatType::OneHandedSaber:
		break;
	case ECombatType::LongStaff:
		break;
	}
}
