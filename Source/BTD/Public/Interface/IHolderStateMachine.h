// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameEnums.h"
#include "IHolderStateMachine.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHolderStateMachine : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BTD_API IIHolderStateMachine
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 切换顶层状态机
	virtual void SwitchTopState(ETopState NewState) = 0;

	// 切换战斗状态机
	virtual void SwitchCombatState(ECombatState NewState) = 0;

	// 切换行为状态机
	virtual void SwitchActionsState(ECharacterBehavior NewState) = 0;

	// 切换移动状态机
	virtual void SwitchMovingState(EMoveState NewState) = 0;

	// 切换旋转状态机
	virtual void SwitchRotationState(EActorRotaType NewState) = 0;

	// 切换武器状态机
	virtual void SwitchWeaponState(ECombatType NewState) = 0;

	// 获取顶层状态机当前状态
	virtual ETopState GetTopState() const = 0;

	// 获取战斗状态机当前状态
	virtual ECombatState GetCombatState() const = 0;

	// 获取行为状态机当前状态
	virtual ECharacterBehavior GetActionsState() const = 0;

	// 获取移动状态机当前状态
	virtual EMoveState GetMovingState() const = 0;

	// 获取旋转状态机当前状态
	virtual EActorRotaType GetRotationState() const = 0;

	// 获取武器状态机当前状态
	virtual ECombatType GetWeaponState() const = 0;
};
