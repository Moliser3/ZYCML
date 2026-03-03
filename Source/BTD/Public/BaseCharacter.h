// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

// 角色旋转类型枚举
UENUM(BlueprintType)
enum class EActorRotaType : uint8
{
	// 默认状态
	Default = 0 UMETA(DisplayName = "Default"),

	// 旋转状态
	Rotating = 1 UMETA(DisplayName = "Rotating"),

	// 注视状态
	Gazing = 2 UMETA(DisplayName = "Gazing")
};

// 角色移动状态枚举
UENUM(BlueprintType)
enum class EMoveState : uint8
{
	// 空闲状态
	Idle = 0 UMETA(DisplayName = "Idle"),

	// 行走状态
	Walking = 1 UMETA(DisplayName = "Walking"),

	// 奔跑状态
	Running = 2 UMETA(DisplayName = "Running")
};

// 角色类型枚举
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	// 主角
	Player = 0 UMETA(DisplayName = "Player"),

	// NPC
	NPC = 1 UMETA(DisplayName = "NPC")
};

UCLASS()
class BTD_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ABaseCharacter();
protected:
    virtual void BeginPlay() override;

private:
    // 角色当前旋转类型状态
    EActorRotaType CurrentRotaType;

    // 存储旋转的目标位置
    FVector TargetRotatePosition;

    // 存储旋转速度
    float CurrentRotationSpeed;

    // 角色当前移动状态
    EMoveState CurrentMoveState;

    // 移动状态检查计时器
    float MoveStateCheckTimer;

    // 上一次记录的位置
    FVector LastRecordedPosition;

    // 保存的旋转目标方向（CheckMoveState计算得出）
    FVector TargetRotationDirection;

public:
    // 移动状态检查的时间间隔（秒），可在蓝图中编辑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
    float MoveStateCheckInterval;

    // 旋转速度（0.0 - 1.0），可在蓝图中编辑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Rotation")
    float RotationSpeed;

    // 不同角度范围对应的旋转速度数组（0-45°, 45-90°, 90-135°, 135-180°）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Rotation")
    TArray<float> AngleRangeRotationSpeeds;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 旋转角色使其面向指定方向，围绕Z轴进行最短弧度旋转
    // TargetDirection: 目标方向向量
    // InRotationSpeed: 旋转速度（0.0 - 1.0，用于Lerp插值）
    void RotateToTargeDirection(const FVector& TargetDirection, float InRotationSpeed = 0.1f);

    // 激活旋转，启动角色向指定方向的旋转过程（仅C++使用）
    // InTargetDirection: 旋转的目标方向向量
    // 旋转速度使用蓝图可编辑的 RotationSpeed 变量
    void ActivateRotation(const FVector& InTargetDirection);

    // 获取当前旋转状态
    UFUNCTION(BlueprintPure, Category = "Character|Rotation")
    EActorRotaType GetRotaType() const { return CurrentRotaType; }

    // 获取当前是否正在旋转
    UFUNCTION(BlueprintPure, Category = "Character|Rotation")
    bool IsRotating() const { return CurrentRotaType != EActorRotaType::Default; }

    // 激活移动状态
    // InMoveState: 要激活的移动状态
    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    void ActiveMove(EMoveState InMoveState);

    // 获取当前移动状态
    UFUNCTION(BlueprintPure, Category = "Character|Movement")
    EMoveState GetMoveState() const { return CurrentMoveState; }

private:
    // 更新旋转状态（根据CurrentRotaType判断是否执行旋转）
    void UpdateRotation();

    // 检测旋转是否完成（forward向量是否已指向目标位置）
    void CheckRotationCompletion();

    // 检查移动状态，根据移动方向调整角色朝向
    void CheckMoveState(float DeltaTime);

    // 旋转完成的角度阈值（度数）
    const float RotationCompletionThreshold = 1.0f;
};