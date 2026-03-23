// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEnums.h"
#include "Interface/IHolderData.h"
//角色的数据黑板
/**
 *
 */
class BTD_API DataModule : public IIHolderData
{
public:
	DataModule();
	~DataModule();

	virtual float GetHealth() const override;
	virtual void SetHealth(float Value) override;

	virtual float GetEnergy() const override;
	virtual void SetEnergy(float Value) override;

	virtual float GetWalkSpeed() const override;
	virtual void SetWalkSpeed(float Value) override;

	virtual float GetRunSpeed() const override;
	virtual void SetRunSpeed(float Value) override;

	virtual float GetRotationSpeed() const override;
	virtual void SetRotationSpeed(float Value) override;

private:
/*需要实现获取和设置方法的属性值-Start*/
	// 血量
	float Health = 100.f;

	// 能量
	float Energy = 100.f;

	// 行走速度
	float WalkSpeed = 250.f;

	// 奔跑速度
	float RunSpeed = 800.f;

	// 旋转速度
	float RotationSpeed = 15.f;

	// 角色旋转类型
	EActorRotaType RotaType = EActorRotaType::Rotating;

	// 移动状态
	EMoveState MoveState = EMoveState::Walking;

	// 角色行为
	ECharacterBehavior CharacterBehavior = ECharacterBehavior::Idle;

	// 战斗状态
	ECombatState CombatState = ECombatState::Idle;

	// 战斗类型
	ECombatType CombatType = ECombatType::Boxing;

	// 角色类型
	ECharacterType CharacterType = ECharacterType::Player;

	// 顶层状态
	ETopState TopState = ETopState::Living;
/*需要实现获取和设置方法的属性值-End*/
};
