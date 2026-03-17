// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FWeaponStateMachine.h"
#include "Interface/IHolderFunction.h"

FWeaponStateMachine::FWeaponStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF)
	: BaseStateMachine(InHolderA, InHolderF)
{
}

FWeaponStateMachine::~FWeaponStateMachine()
{
}
