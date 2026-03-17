// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BTD_API IState
{
public:
    virtual ~IState();
    virtual void OnEnter() =0;
    virtual void OnUpdate(float DeltaTime) =0;
    virtual void OnExit() =0;

    
};