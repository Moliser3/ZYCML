// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FBaseAnimation.h"

#include "GameEnums.h"

void UFBaseAnimation::SetIdleToCombat(const float InIdleToCombat)
{
    CombatPose = InIdleToCombat;
}

void UFBaseAnimation::SwitchBehaviourState(const ECharacterBehavior NewBehavior)
{
    CharacterBehavior = NewBehavior;
}

void UFBaseAnimation::SwitchMoveState(const EMoveState NewMoveState)
{
    MoveState = NewMoveState;
}