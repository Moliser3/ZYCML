// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IHolderAttribute.h"
#include "Interface/IHolderStateMachine.h"
enum class EActorRotaType : uint8;
/**
 * 
 */
class BTD_API FRotationModule
{
public:
	explicit FRotationModule(IIHolderAttribute* InHolderA, IIHolderStateMachine* InHolderM);
	~FRotationModule();

	// 更新旋转状态（根据CurrentRotaType判断是否执行旋转）
	void RotationModuleTick();
	//在Begin中进行模块初始化
	void InitRotationModel(const TArray<float>& InAngleRangeRotationSpeeds);

private:
	// 持有者接口，用于获取位置等信息
	IIHolderAttribute* HolderAttribute;
	IIHolderStateMachine* HolderStateMachine;
	// 不同角度范围对应的旋转速度数组（0-45°, 45-90°, 90-135°, 135-180°）
	TArray<float> AngleRangeRotationSpeeds;

	// // 保存的旋转目标方向（CheckMoveState计算得出）
	FVector TargetRotationDirection;

	// 旋转完成的角度阈值（度数）
	const float RotationCompletionThreshold = 1.0f;

	void CheckRotationCompletion() const;
	// 旋转角色使其面向指定方向，围绕Z轴进行最短弧度旋转
	// TargetDirection: 目标方向向量
	// InRotationSpeed: 旋转速度（0.0 - 1.0，用于Lerp插值）
	void RotateToTargetDirection(const FVector& TargetDirection);
};
