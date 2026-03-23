// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FBaseAnimation.h"

#include "GameEnums.h"

void UFBaseAnimation::SetIdleToCombat(const float InIdleToCombat)
{
    CombatPose = InIdleToCombat;
}

void UFBaseAnimation::SwitchTopState(ETopState NewState)
{
    TopState = NewState;
}

void UFBaseAnimation::SwitchCombatState(ECombatState NewState)
{
    CombatState = NewState;
}

void UFBaseAnimation::SwitchBehaviourState(ECharacterBehavior NewBehavior)
{
    CharacterBehavior = NewBehavior;
}

void UFBaseAnimation::SwitchMoveState(EMoveState NewMoveState)
{
    MoveState = NewMoveState;
}

void UFBaseAnimation::SwitchRotationType(EActorRotaType NewRotationType)
{
    RotationType = NewRotationType;
}

void UFBaseAnimation::SwitchCombatType(ECombatType NewCombatType)
{
    CombatType = NewCombatType;
}