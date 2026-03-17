// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameEnums.h"
#include "IHolderFunction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHolderFunction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BTD_API IIHolderFunction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 切换顶层状态机的状态
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Function")
	void SwitchTopState(ETopState InTopState);

	// 改变角色战斗状态
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Function")
	void SwitchCombatState(ECombatState InCharacterState);

	// 改变战斗动画（切换战斗类型并将行为状态设为攻击）
	UFUNCTION(BlueprintNativeEvent, Category = "Interface|Function")
	void SwitchCombatAnimation(const float Value);
};
