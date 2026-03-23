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
    //设置移动组件的移动速度
    UFUNCTION(BlueprintNativeEvent, Category = "Interface|Function")
    void  SetMovementSpeed(const float Value);
};