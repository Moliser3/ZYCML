// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IHolderStateMachine.h"

class IIHolderAttribute;
class IIHolderFunction;
class IIHolderData;
class FActionsStateMachine;
class FCombatStateMachine;
class FMovingStateMachine;
class FRotationStateMachine;
class FTopStateMachine;
class FWeaponStateMachine;

// 状态变化委托
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTopStateChanged,      ETopState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCombatStateChanged,   ECombatState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActionsStateChanged,  ECharacterBehavior);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovingStateChanged,   EMoveState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRotationStateChanged, EActorRotaType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponStateChanged,   ECombatType);

/**
 *
 */
class BTD_API FStateMachineModule : public IIHolderStateMachine
{
public:
	FStateMachineModule(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF, IIHolderData* InHolderD);
	~FStateMachineModule();

	void Tick(float DeltaTime);

	// 状态变化委托（供外部注册）
	FOnTopStateChanged      OnTopStateChanged;
	FOnCombatStateChanged   OnCombatStateChanged;
	FOnActionsStateChanged  OnActionsStateChanged;
	FOnMovingStateChanged   OnMovingStateChanged;
	FOnRotationStateChanged OnRotationStateChanged;
	FOnWeaponStateChanged   OnWeaponStateChanged;

	// 切换方法
	virtual void SwitchTopState(ETopState NewState) override;
	virtual void SwitchCombatState(ECombatState NewState) override;
	virtual void SwitchActionsState(ECharacterBehavior NewState) override;
	virtual void SwitchMovingState(EMoveState NewState) override;
	virtual void SwitchRotationState(EActorRotaType NewState) override;
	virtual void SwitchWeaponState(ECombatType NewState) override;

	// 获取当前状态方法
	virtual ETopState GetTopState() const override;
	virtual ECombatState GetCombatState() const override;
	virtual ECharacterBehavior GetActionsState() const override;
	virtual EMoveState GetMovingState() const override;
	virtual EActorRotaType GetRotationState() const override;
	virtual ECombatType GetWeaponState() const override;

private:
	IIHolderAttribute* HolderAttribute;
	IIHolderFunction* HolderFunction;
	IIHolderData* HolderData;

	FActionsStateMachine* ActionsStateMachine;
	FCombatStateMachine* CombatStateMachine;
	FMovingStateMachine* MovingStateMachine;
	FRotationStateMachine* RotationStateMachine;
	FTopStateMachine* TopStateMachine;
	FWeaponStateMachine* WeaponStateMachine;

	// 当前状态属性
	ETopState CurrentTopState = ETopState::Living;
	ECombatState CurrentCombatState = ECombatState::Idle;
	ECharacterBehavior CurrentActionsState = ECharacterBehavior::Idle;
	EMoveState CurrentMovingState = EMoveState::Walking;
	EActorRotaType CurrentRotationState = EActorRotaType::Rotating;
	ECombatType CurrentWeaponState = ECombatType::Boxing;
};
