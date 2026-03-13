// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//enum class EActorRotaType : uint8;
///**
// * 
// */
class BTD_API ActorRotation
{
public:
    ActorRotation();
   
    ~ActorRotation();
    /*
    // 更新旋转状态（根据CurrentRotaType判断是否执行旋转）
    void RotationTick(FVector TargetLocation, FVector CurrentLocation);
    */
private:

    /*
    // 角色当前旋转类型状态
    EActorRotaType CurrentRotaType;
    // 存储旋转的目标位置
    FVector TargetRotatePosition;
    // 存储旋转速度
    float CurrentRotationSpeed;
    // 保存的旋转目标方向（CheckMoveState计算得出）
    FVector TargetRotationDirection;

    void CheckRotationCompletion();
    // 旋转角色使其面向指定方向，围绕Z轴进行最短弧度旋转
    // TargetDirection: 目标方向向量
    // InRotationSpeed: 旋转速度（0.0 - 1.0，用于Lerp插值）
    void RotateToTargeDirection(const FVector& TargetDirection, float InRotationSpeed = 0.1f);

    // 激活旋转，启动角色向指定方向的旋转过程（仅C++使用）
    // InTargetDirection: 旋转的目标方向向量
    // 旋转速度使用蓝图可编辑的 RotationSpeed 变量
    void ActivateRotation(const FVector& InTargetDirection);
    */
};