// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/FTopState.h"

#include "Interface/IHolderAttribute.h"

FTopState::FTopState(IIHolderAttribute* InHolder, const ETopState InputState) : BaseState(InHolder)
{
    CurrentState = InputState;
}

FTopState::~FTopState()
{
}

void FTopState::OnEnter()
{
    switch (CurrentState)
    {
    case ETopState::Living:
        UE_LOG(LogTemp, Log, TEXT("获得新生"));
        break;
    case ETopState::Dead:
        UE_LOG(LogTemp, Log, TEXT("获得死亡"));
        break;
    }
}

void FTopState::OnUpdate(float DeltaTime)
{
    switch (CurrentState)
    {
    case ETopState::Living:
        UE_LOG(LogTemp, Log, TEXT("新生ing"));
        break;
    case ETopState::Dead:
        UE_LOG(LogTemp, Log, TEXT("死亡ing"));
        break;
    }
}

void FTopState::OnExit()
{
    switch (CurrentState)
    {
    case ETopState::Living:
        UE_LOG(LogTemp, Log, TEXT("退出新生"));
        break;
    case ETopState::Dead:
        UE_LOG(LogTemp, Log, TEXT("退出死亡"));
        break;
    }
}