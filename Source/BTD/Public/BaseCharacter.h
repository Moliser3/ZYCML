// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDataStruct.h"
#include "GameFramework/Character.h"
#include "Interface/IActorProperty.h"
#include "Interface/IHolderAttribute.h"
#include "GameEnums.h"
#include "Interface/IHolderFunction.h"
#include "Animation/FBaseAnimation.h"
#include "BaseCharacter.generated.h"

class FRotationModule;
class FMovingModule;
class DataModule;
class FStateMachineModule;

UCLASS()
class BTD_API ABaseCharacter : public ACharacter, public IIHolderAttribute, public IIHolderFunction
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual ~ABaseCharacter() override;

protected:
	virtual void BeginPlay() override;

private:
	// 数据模块
	DataModule* CharacterDataModule;
	// 状态机模块
	FStateMachineModule* StateMachineModule;
	//移动模块
	FMovingModule* MovingModule;
	//旋转模块
	FRotationModule* RotationModule;

	// 当前移动速度
	float CurrentMoveSpeed;

	// 保存的旋转目标方向（CheckMoveState计算得出）
	FVector TargetRotationDirection;

	// 保存外部传入的目标属性接口
	TScriptInterface<IIActorProperty> ExternalTargetProperty;
	// 动画实例
	UFBaseAnimation* BaseAnimation;
	// 移动方向委托句柄
	FDelegateHandle MoveDirectionChangedHandle;

public:
	// 不同角度范围对应的旋转速度数组（0-45°, 45-90°, 90-135°, 135-180°）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Rotation")
	TArray<float> AngleRangeRotationSpeeds;

	// 角色类型（主角或NPC），可在蓝图中编辑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType CharacterType;

	// 角色数据（血量、能量、移动速度），可在蓝图中编辑（用于初始配置，BeginPlay 时同步至 DataModule）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
	FCharacterData CharacterData;

	// 目标角色引用，可在蓝图中编辑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ABaseCharacter* TargetActor;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 实现 IIHolderFunction 接口：激活旋转状态
	virtual void ActivateRotating_Implementation() override;

	// 实现 IIHolderFunction 接口：激活注视状态
	virtual void ActiveGazing_Implementation() override;

	// 激活移动状态（根据当前移动状态执行对应逻辑）
	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void BeginActiveMove();

	// 移动结束回调
	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void OnMoveEnd();

	// 设置目标角色
	// InTargetActor: 要设置的目标BaseCharacter
	UFUNCTION(BlueprintCallable, Category = "Character|Target")
	void SetTargetActor(ABaseCharacter* InTargetActor);

	// 获取目标角色
	UFUNCTION(BlueprintPure, Category = "Character|Target")
	ABaseCharacter* GetTargetActor() const { return TargetActor; }

	// 蓝图切换移动状态
	UFUNCTION(BlueprintCallable, Category = "Character|Target")
	void SetMoveState(EMoveState InMoveState);

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

	// 实现 IIHolderAttribute 接口：设置当前旋转类型状态
	virtual void SetCurrentRotaType_Implementation(EActorRotaType NewRotaType) override;


	// 实现 IIHolderAttribute 接口：返回当前角色的目标旋转方向
	virtual FVector GetTargetRotationDirection_Implementation() const override;

	// 实现 IIHolderAttribute 接口：返回当前角色的行为状态

	// 实现 IIHolderAttribute 接口：设置当前角色的目标旋转方向
	virtual void SetTargetRotationDirection_Implementation(const FVector& NewDirection) override;

	//	实现 设置移动组件的移动速度
	virtual void SetMovementSpeed_Implementation(const float Value) override;

	// 实现 IIHolderAttribute 接口：获取当前移动方向
	virtual EMoveDirection GetMoveDirection_Implementation() const override;

private:
};
