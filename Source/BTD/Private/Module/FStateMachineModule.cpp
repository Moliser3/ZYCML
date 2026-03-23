// Fill out your copyright notice in the Description page of Project Settings.


#include "Module/FStateMachineModule.h"
#include "StateMachine/FActionsStateMachine.h"
#include "StateMachine/FCombatStateMachine.h"
#include "StateMachine/FMovingStateMachine.h"
#include "StateMachine/FRotationStateMachine.h"
#include "StateMachine/FTopStateMachine.h"
#include "StateMachine/FWeaponStateMachine.h"
#include "StateMachine/FActionsState.h"
#include "StateMachine/FCombatState.h"
#include "StateMachine/FMovingState.h"
#include "StateMachine/FRotationState.h"
#include "StateMachine/FTopState.h"
#include "StateMachine/FWeaponState.h"

FStateMachineModule::FStateMachineModule(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD)
	: HolderAttribute(InHolderA), HolderFunction(InHolderF), HolderData(InHolderD)
{
	TopStateMachine = new FTopStateMachine(InHolderA, InHolderF);
	TopStateMachine->Transition(new FTopState(InHolderA, InHolderF, InHolderD, this, ETopState::Living));
	CombatStateMachine = new FCombatStateMachine(InHolderA, InHolderF);
	CombatStateMachine->Transition(new FCombatState(InHolderA, InHolderF, InHolderD, this, ECombatState::Idle));
	ActionsStateMachine = new FActionsStateMachine(InHolderA, InHolderF);
	ActionsStateMachine->Transition(new FActionsState(InHolderA, InHolderF, InHolderD, this, ECharacterBehavior::Idle));
	MovingStateMachine = new FMovingStateMachine(InHolderA, InHolderF);
	MovingStateMachine->Transition(new FMovingState(InHolderA, InHolderF, InHolderD, this, EMoveState::Walking));
	RotationStateMachine = new FRotationStateMachine(InHolderA, InHolderF);
	RotationStateMachine->Transition(new FRotationState(InHolderA, InHolderF, InHolderD, this, EActorRotaType::Rotating));
	WeaponStateMachine = new FWeaponStateMachine(InHolderA, InHolderF);
	WeaponStateMachine->Transition(new FWeaponState(InHolderA, InHolderF, InHolderD, this, ECombatType::Boxing));
}

FStateMachineModule::~FStateMachineModule()
{
	delete TopStateMachine;
	TopStateMachine = nullptr;
	delete CombatStateMachine;
	CombatStateMachine = nullptr;
	delete ActionsStateMachine;
	ActionsStateMachine = nullptr;
	delete MovingStateMachine;
	MovingStateMachine = nullptr;
	delete RotationStateMachine;
	RotationStateMachine = nullptr;
	delete WeaponStateMachine;
	WeaponStateMachine = nullptr;

	OnTopStateChanged.Clear();
	OnCombatStateChanged.Clear();
	OnActionsStateChanged.Clear();
	OnMovingStateChanged.Clear();
	OnRotationStateChanged.Clear();
	OnWeaponStateChanged.Clear();
}

void FStateMachineModule::Tick(float DeltaTime)
{
	TopStateMachine->Update(DeltaTime);
	CombatStateMachine->Update(DeltaTime);
	ActionsStateMachine->Update(DeltaTime);
	MovingStateMachine->Update(DeltaTime);
	RotationStateMachine->Update(DeltaTime);
	WeaponStateMachine->Update(DeltaTime);
}

/*切换状态机 Start*/
void FStateMachineModule::SwitchTopState(ETopState NewState)
{
	CurrentTopState = NewState;
	TopStateMachine->Transition(new FTopState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnTopStateChanged.Broadcast(NewState);
}

void FStateMachineModule::SwitchCombatState(ECombatState NewState)
{
	CurrentCombatState = NewState;
	CombatStateMachine->Transition(new FCombatState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnCombatStateChanged.Broadcast(NewState);
}

void FStateMachineModule::SwitchActionsState(ECharacterBehavior NewState)
{
	CurrentActionsState = NewState;
	ActionsStateMachine->Transition(new FActionsState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnActionsStateChanged.Broadcast(NewState);
}

void FStateMachineModule::SwitchMovingState(EMoveState NewState)
{
	CurrentMovingState = NewState;
	MovingStateMachine->Transition(new FMovingState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnMovingStateChanged.Broadcast(NewState);
}

void FStateMachineModule::SwitchRotationState(EActorRotaType NewState)
{
	CurrentRotationState = NewState;
	RotationStateMachine->Transition(new FRotationState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnRotationStateChanged.Broadcast(NewState);
}

void FStateMachineModule::SwitchWeaponState(ECombatType NewState)
{
	CurrentWeaponState = NewState;
	WeaponStateMachine->Transition(new FWeaponState(HolderAttribute, HolderFunction, HolderData, this, NewState));
	OnWeaponStateChanged.Broadcast(NewState);
}

/*切换状态机 End*/

/*获取当前状态 Start*/
ETopState FStateMachineModule::GetTopState() const
{
	return CurrentTopState;
}

ECombatState FStateMachineModule::GetCombatState() const
{
	return CurrentCombatState;
}

ECharacterBehavior FStateMachineModule::GetActionsState() const
{
	return CurrentActionsState;
}

EMoveState FStateMachineModule::GetMovingState() const
{
	return CurrentMovingState;
}

EActorRotaType FStateMachineModule::GetRotationState() const
{
	return CurrentRotationState;
}

ECombatType FStateMachineModule::GetWeaponState() const
{
	return CurrentWeaponState;
}

/*获取当前状态 End*/
