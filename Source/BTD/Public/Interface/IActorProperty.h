// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IActorProperty.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIActorProperty : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class BTD_API IIActorProperty
{
	GENERATED_BODY()
	
public:
	// 获取对象的位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Property")
	FVector GetLocation() const;
};
