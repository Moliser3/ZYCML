// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/IActorProperty.h"
#include "Interface/IHolderAttribute.h"
#include "GameEnums.h"
#include "CharacterDataStruct.h"
#include "BaseCharacter.generated.h"


class FTopStateMachine;
class FRotationModule;
class FMovingModule;
// 行为状态变化委托（当前行为, 当前移动状态）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBehaviorChanged, ECharacterBehavior, CurrentBehavior, EMoveState, CurrentMoveState);

// 战斗类型变化委托（当前战斗类型）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatTypeChanged, ECombatType, CurrentCombatType);

// 角色状态变化委托（当前角色状态）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanged, ECharacterState, CurrentCharacterState);


UCLASS()
class BTD_API ABaseCharacter : public ACharacter, public IIActorProperty, public IIHolderAttribute
{
    GENERATED_BODY()

public:
    ABaseCharacter();
    virtual ~ABaseCharacter() override;

protected:
    virtual void BeginPlay() override;

private:
    //移动模块
    FMovingModule* MovingModule;
    //旋转模块
    FRotationModule* RotationModule;

    // 角色当前旋转类型状态
    EActorRotaType CurrentRotaType;

    // 角色当前移动状态
    EMoveState CurrentMoveState;

    // 当前移动速度
    float CurrentMoveSpeed;

    // 保存的旋转目标方向（CheckMoveState计算得出）
    FVector TargetRotationDirection;

    // 角色当前行为状态
    ECharacterBehavior CurrentBehavior;

    // 当前战斗类型
    ECombatType CurrentCombatType;

    // 当前角色状态
    ECharacterState CurrentCharacterState;

    // 保存外部传入的目标属性接口
    TScriptInterface<IIActorProperty> ExternalTargetProperty;

    /*状态机*/
    FTopStateMachine* TopStateMachine;

public:
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

    // 行为状态变化时广播  委托
    UPROPERTY(BlueprintAssignable, Category = "Character|Behavior")
    FOnBehaviorChanged OnBehaviorChanged;

    // 战斗类型变化时广播  委托
    UPROPERTY(BlueprintAssignable, Category = "Character|Combat")
    FOnCombatTypeChanged OnCombatTypeChanged;

    // 角色状态变化时广播  委托
    UPROPERTY(BlueprintAssignable, Category = "Character|State")
    FOnCharacterStateChanged OnCharacterStateChanged;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

    // 激活战斗行为（切换战斗类型并将行为状态设为战斗）
    UFUNCTION(BlueprintCallable, Category = "Character|Combat")
    void ActivateCombat(ECombatType InCombatType);

    // 获取当前战斗类型
    UFUNCTION(BlueprintPure, Category = "Character|Combat")
    ECombatType GetCombatType() const { return CurrentCombatType; }

    // 设置角色状态
    UFUNCTION(BlueprintCallable, Category = "Character|State")
    void SetCharacterState(ECharacterState InCharacterState);

    // 获取当前角色状态
    UFUNCTION(BlueprintPure, Category = "Character|State")
    ECharacterState GetCharacterState() const { return CurrentCharacterState; }

    // 设置目标角色
    // InTargetActor: 要设置的目标BaseCharacter
    UFUNCTION(BlueprintCallable, Category = "Character|Target")
    void SetTargetActor(ABaseCharacter* InTargetActor) { TargetActor = InTargetActor; }

    // 获取目标角色
    UFUNCTION(BlueprintPure, Category = "Character|Target")
    ABaseCharacter* GetTargetActor() const { return TargetActor; }


    // 实现 IIActorProperty / IIHolderAttribute 接口：返回当前角色的世界坐标位置
    virtual FVector GetLocation_Implementation() const override;

    // 实现 IIHolderAttribute 接口：返回当前角色的正方向向量
    virtual FVector GetForwardVector_Implementation() const override;

    // 实现 IIHolderAttribute 接口：返回目标角色的位置
    virtual FVector GetTargetLocation_Implementation() const override;

    // 实现 IIHolderAttribute 接口：返回当前角色的旋转角度
    virtual FRotator GetRotation_Implementation() const override;

    // 实现 IIHolderAttribute 接口：设置当前角色的旋转角度
    virtual void SetHolderRotation_Implementation(FRotator NewRotation) override;

    // 实现 IIHolderAttribute 接口：返回当前角色的旋转类型状态
    virtual EActorRotaType GetCurrentRotaType_Implementation() const override;

    // 实现 IIHolderAttribute 接口：设置当前角色的旋转类型状态
    virtual void SetCurrentRotaType_Implementation(EActorRotaType NewRotaType) override;

    // 实现 IIHolderAttribute 接口：返回当前角色的目标旋转方向
    virtual FVector GetTargetRotationDirection_Implementation() const override;

    // 实现 IIHolderAttribute 接口：返回当前角色的行为状态
    virtual ECharacterBehavior GetBehaviorState_Implementation() const override;

    // 实现 IIHolderAttribute 接口：设置当前角色的目标旋转方向
    virtual void SetTargetRotationDirection_Implementation(const FVector& NewDirection) override;

private:
    // 切换移动状态并将CharacterData中对应的速度应用到移动组件
    void SetMoveState(EMoveState InMoveState);

    // 设置行为状态并广播变化
    void SetBehavior(ECharacterBehavior NewBehavior);

    // 旋转完成的角度阈值（度数）
    const float RotationCompletionThreshold = 1.0f;
};