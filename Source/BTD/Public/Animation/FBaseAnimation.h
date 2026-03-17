// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FBaseAnimation.generated.h"

/**
 * 
 */
UCLASS()
class BTD_API UFBaseAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|IdleToCombat")
	float IdleToCombat;

	void SetIdleToCombat(float InIdleToCombat);
};
