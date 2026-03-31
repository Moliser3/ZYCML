// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FBaseAnimation.generated.h"

enum class EMoveState : uint8;
enum class ECharacterBehavior : uint8;
enum class ETopState : uint8;
enum class ECombatState : uint8;
enum class EActorRotaType : uint8;
enum class ECombatType : uint8;
enum class EMoveDirection : uint8;
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

    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    ETopState TopState;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    ECombatState CombatState;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    ECharacterBehavior CharacterBehavior;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    EMoveState MoveState;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    EActorRotaType RotationType;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    ECombatType CombatType;
    UPROPERTY(BlueprintReadOnly, Category = "Animation|State")
    EMoveDirection MoveDirection;

    void SetIdleToCombat(const float InIdleToCombat);
    void SwitchTopState(ETopState NewState);
    void SwitchCombatState(ECombatState NewState);
    void SwitchBehaviourState(ECharacterBehavior NewBehavior);
    void SwitchMoveState(EMoveState NewMoveState);
    void SwitchRotationType(EActorRotaType NewRotationType);
    void SwitchCombatType(ECombatType NewCombatType);
    void SwitchMoveDirection(EMoveDirection NewMoveDirection);
};