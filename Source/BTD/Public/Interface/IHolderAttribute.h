// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameEnums.h"
#include "IHolderAttribute.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHolderAttribute : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BTD_API IIHolderAttribute
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 获取持有者的位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	FVector GetLocation() const;

	// 获取持有者的正方向向量
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	FVector GetForwardVector() const;

	// 获取目标的位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	FVector GetTargetLocation() const;

	// 获取持有者的旋转角度
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	FRotator GetRotation() const;

	// 设置持有者的旋转角度
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	void SetHolderRotation(FRotator NewRotation);


	// 设置持有者的旋转类型状态
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	void SetCurrentRotaType(EActorRotaType NewRotaType);

	// 获取持有者的目标旋转方向
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	FVector GetTargetRotationDirection() const;

	// 设置持有者的目标旋转方向
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Holder")
	void SetTargetRotationDirection(const FVector& NewDirection);
};
