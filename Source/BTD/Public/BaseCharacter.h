// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/IActorProperty.h"
#include "GameEnums.h"
#include "CharacterDataStruct.h"
#include "BaseCharacter.generated.h"


// 行为状态变化委托（当前行为, 当前移动状态）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBehaviorChanged, ECharacterBehavior, CurrentBehavior, EMoveState, CurrentMoveState);

UCLASS()
class BTD_API ABaseCharacter : public ACharacter, public IIActorProperty
{
    GENERATED_BODY()

public:
    ABaseCharacter();

protected:
    virtual void BeginPlay() override;

private:
    //TUniquePtr<ActorRotation> ActorRotationModel;

    // 角色当前旋转类型状态
    EActorRotaType CurrentRotaType;

    // 存储旋转的目标位置
    FVector TargetRotatePosition;

    // 存储旋转速度
    float CurrentRotationSpeed;

    // 角色当前移动状态
    EMoveState CurrentMoveState;

    // 当前移动速度
    float CurrentMoveSpeed;

    // 移动状态检查计时器
    float MoveStateCheckTimer;

    // 上一次记录的位置
    FVector LastRecordedPosition;

    // 保存的旋转目标方向（CheckMoveState计算得出）
    FVector TargetRotationDirection;

    // 角色当前行为状态
    ECharacterBehavior CurrentBehavior;

    // 保存外部传入的目标属性接口
    TScriptInterface<IIActorProperty> ExternalTargetProperty;

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

    // 角色类型（主角或NPC），可在蓝图中编辑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    ECharacterType CharacterType;

    // 角色数据（血量、能量、移动速度），可在蓝图中编辑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
    FCharacterData CharacterData;

    // 目标角色引用，可在蓝图中编辑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    ABaseCharacter* TargetActor;

    // 行为状态变化时广播
    UPROPERTY(BlueprintAssignable, Category = "Character|Behavior")
    FOnBehaviorChanged OnBehaviorChanged;

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

    // 激活注视：使角色正面永远看向TargetActor的位置
    UFUNCTION(BlueprintCallable, Category = "Character|Target")
    void ActiveGazing();

    // 获取当前是否正在旋转
    UFUNCTION(BlueprintPure, Category = "Character|Rotation")
    bool IsRotating() const { return CurrentRotaType != EActorRotaType::Default; }

    // 激活移动状态（根据当前移动状态执行对应逻辑）
    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    void BeginActiveMove();

    // 移动结束回调
    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    void OnMoveEnd();

    // 激活奔跑
    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    void ActivateRunning();

    // 激活步行
    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    void ActivateWalking();

    // 获取当前移动状态
    UFUNCTION(BlueprintPure, Category = "Character|Movement")
    EMoveState GetMoveState() const { return CurrentMoveState; }

    // 获取当前行为状态
    UFUNCTION(BlueprintPure, Category = "Character|Behavior")
    ECharacterBehavior GetBehavior() const { return CurrentBehavior; }

    // 设置目标角色
    // InTargetActor: 要设置的目标BaseCharacter
    UFUNCTION(BlueprintCallable, Category = "Character|Target")
    void SetTargetActor(ABaseCharacter* InTargetActor) { TargetActor = InTargetActor; }

    // 获取目标角色
    UFUNCTION(BlueprintPure, Category = "Character|Target")
    ABaseCharacter* GetTargetActor() const { return TargetActor; }


    // 实现 IIActorProperty 接口：返回当前角色的世界坐标位置
    virtual FVector GetLocation_Implementation() const override;

private:
    // 切换移动状态并将CharacterData中对应的速度应用到移动组件
    void SetMoveState(EMoveState InMoveState);

    // 设置行为状态并广播变化
    void SetBehavior(ECharacterBehavior NewBehavior);

    // 根据移动状态切换旋转模式
    void ActiveRota();

    // 更新旋转状态（根据CurrentRotaType判断是否执行旋转）
    void UpdateRotation();

    // 检测旋转是否完成（forward向量是否已指向目标位置）
    void CheckRotationCompletion();

    // 检查移动状态，根据移动方向调整角色朝向
    void CheckMoveState(float DeltaTime);

    // 旋转完成的角度阈值（度数）
    const float RotationCompletionThreshold = 1.0f;
};