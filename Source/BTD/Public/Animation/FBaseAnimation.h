// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FBaseAnimation.generated.h"

enum class EMoveState : uint8;
enum class ECharacterBehavior : uint8;
/**
 * 
 */
UCLASS()
class BTD_API UFBaseAnimation : public UAnimInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Property")
    float CombatPose;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Property")
    ECharacterBehavior CharacterBehavior;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Property")
    EMoveState MoveState;
    void SetIdleToCombat(const float InIdleToCombat);
    void SwitchBehaviourState(const ECharacterBehavior NewBehavior);
    void SwitchMoveState(const EMoveState NewMoveState);
};