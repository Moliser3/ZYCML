// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseStateMachine.h"
#include "Interface/IState.h"

BaseStateMachine::BaseStateMachine(IIHolderAttribute* InHolder) : InHolderAttribute(InHolder), CurrentState(nullptr)
{
}

BaseStateMachine::~BaseStateMachine()
{
}

void BaseStateMachine::Transition(IState* NewState)
{
    if (CurrentState)
        CurrentState->OnExit();
    CurrentState = NewState;
    CurrentState->OnEnter();
}

void BaseStateMachine::Update(const float DeltaTime)
{
    if (!CurrentState)
        return;
    CurrentState->OnUpdate(DeltaTime);
}