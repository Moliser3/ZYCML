// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IIHolderFunction;
class IIHolderAttribute;
class IState;
/**
 * 
 */
class BTD_API BaseStateMachine
{
public:
	//带有IIHolderAttribute参数的构造函数，用于初始化状态机时传入持有者属性接口
	explicit BaseStateMachine(IIHolderAttribute* InHolderA, IIHolderFunction* InHolderF);
	~BaseStateMachine();
	void Transition(IState* NewState);
	void Update(const float DeltaTime) const;

protected:
	IIHolderAttribute* InHolderAttribute;
	IIHolderFunction* InHolderFunction;

private:
	IState* CurrentState;
};
