// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRotation.h"

#include "GameEnums.h"

ActorRotation::ActorRotation()
{
}

ActorRotation::~ActorRotation()
{
}
/*
void ActorRotation::RotationTick(FVector TargetLocation, FVector CurrentLocation)
{
    // 如果旋转状态不是默认状态，执行旋转更新
    if (CurrentRotaType != EActorRotaType::Default)
    {
        // 如果是Gazing状态且有有效的目标，实时更新目标方向
        if (CurrentRotaType == EActorRotaType::Gazing)
        {
            // 计算指向目标的方向
            FVector DirectionToTarget = (TargetLocation - CurrentLocation);
            DirectionToTarget.Z = 0.0f; // 只在水平面上旋转

            // 归一化方向
            if (!DirectionToTarget.IsNormalized())
            {
                DirectionToTarget.Normalize();
            }

            // 如果方向有效，更新目标旋转方向
            if (!DirectionToTarget.IsZero())
            {
                TargetRotationDirection = DirectionToTarget;
            }
            else
            {
                // 目标与自己在同一位置，停止Gazing
                CurrentRotaType = EActorRotaType::Default;
                return;
            }
        }

        RotateToTargeDirection(TargetRotationDirection, CurrentRotationSpeed);

        // 检测旋转是否完成（仅针对非Gazing状态）
        if (CurrentRotaType != EActorRotaType::Gazing)
        {
            CheckRotationCompletion();
        }
    }
}

void ActorRotation::CheckRotationCompletion()
{
    // 如果无法计算有效方向，则不进行检测
    if (!TargetRotationDirection.IsNormalized())
    {
        return;
    }

    // 获取当前角色的Forward向量（仅X、Y平面）
    FVector CurrentForward = GetActorForwardVector();
    CurrentForward.Z = 0.0f;
    CurrentForward.Normalize();

    // 计算两个向量之间的夹角
    float DotProduct = FVector::DotProduct(CurrentForward, TargetRotationDirection);
    // 夹角值范围在-1到1之间，Clamp确保不会有浮点误差导致的异常
    DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
    float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);

    // 如果夹角小于阈值，说明Forward向量已经指向目标方向，停止旋转
    if (AngleDifference < RotationCompletionThreshold)
    {
        CurrentRotaType = EActorRotaType::Default;
    }
}

void ActorRotation::RotateToTargeDirection(const FVector& TargetDirection, float InRotationSpeed)
{
    // 规范化目标方向向量（仅使用X、Y平面，忽略Z轴）
    FVector NormalizedDirection = TargetDirection;
    NormalizedDirection.Z = 0.0f; // 清零Z轴分量，确保只在水平面上旋转
    NormalizedDirection.Normalize(); // 归一化方向向量

    // 处理零向量的情况
    if (!NormalizedDirection.IsNormalized())
    {
        return; // 如果无法计算有效方向，则不进行旋转
    }

    // 获取当前Forward向量
    FVector CurrentForward = GetActorForwardVector();
    CurrentForward.Z = 0.0f;
    CurrentForward.Normalize();

    // 计算当前Forward和目标方向的夹角
    float DotProduct = FVector::DotProduct(CurrentForward, NormalizedDirection);
    DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
    float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);

    // 根据夹角范围选择对应的旋转速度
    float FinalRotationSpeed = InRotationSpeed;
    if (AngleRangeRotationSpeeds.Num() >= 4)
    {
        if (AngleDifference < 45.0f)
        {
            FinalRotationSpeed = AngleRangeRotationSpeeds[0]; // 0-45度
        }
        else if (AngleDifference < 90.0f)
        {
            FinalRotationSpeed = AngleRangeRotationSpeeds[1]; // 45-90度
        }
        else if (AngleDifference < 135.0f)
        {
            FinalRotationSpeed = AngleRangeRotationSpeeds[2]; // 90-135度
        }
        else
        {
            FinalRotationSpeed = AngleRangeRotationSpeeds[3]; // 135-180度
        }
    }

    // 获取当前旋转信息
    FRotator CurrentRotation = GetActorRotation();
    float CurrentYaw = CurrentRotation.Yaw;

    // 计算目标方向相对于世界坐标系的Yaw角度
    float TargetYaw = FMath::Atan2(NormalizedDirection.Y, NormalizedDirection.X) * (180.0f / PI);

    // 计算旋转差值
    float YawDelta = TargetYaw - CurrentYaw;

    // 选择最短旋转路径（-180到180之间）
    if (YawDelta > 180.0f)
    {
        YawDelta -= 360.0f;
    }
    else if (YawDelta < -180.0f)
    {
        YawDelta += 360.0f;
    }

    // 使用Lerp进行平滑旋转
    float NewYaw = FMath::Lerp(CurrentYaw, CurrentYaw + YawDelta, FinalRotationSpeed);

    // 应用新的旋转
    FRotator NewRotation = CurrentRotation;
    NewRotation.Yaw = NewYaw;
    SetActorRotation(NewRotation);
}

void ActorRotation::ActivateRotation(const FVector& InTargetDirection)
{
}
*/