// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameEnums.h"
#include "IHolderData.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHolderData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BTD_API IIHolderData
{
	GENERATED_BODY()

	
public:
	// 血量
	virtual float GetHealth() const = 0;
	virtual void SetHealth(float Value) = 0;

	// 能量
	virtual float GetEnergy() const = 0;
	virtual void SetEnergy(float Value) = 0;

	// 行走速度
	virtual float GetWalkSpeed() const = 0;
	virtual void SetWalkSpeed(float Value) = 0;

	// 奔跑速度
	virtual float GetRunSpeed() const = 0;
	virtual void SetRunSpeed(float Value) = 0;

	// 旋转速度
	virtual float GetRotationSpeed() const = 0;
	virtual void SetRotationSpeed(float Value) = 0;

};
