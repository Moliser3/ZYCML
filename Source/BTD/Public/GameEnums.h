// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEnums.generated.h"

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
	// 行走状态
	Walking = 0 UMETA(DisplayName = "Walking"),

	// 奔跑状态
	Running = 1 UMETA(DisplayName = "Running")
};

// 角色行为枚举
UENUM(BlueprintType)
enum class ECharacterBehavior : uint8
{
	// 闲置
	Idle = 0 UMETA(DisplayName = "Idle"),

	// 移动
	Moving = 1 UMETA(DisplayName = "Moving"),

	// 死亡
	Death = 2 UMETA(DisplayName = "Death"),

	// 跳跃
	Jump = 3 UMETA(DisplayName = "Jump"),

	// 受击
	Hit = 4 UMETA(DisplayName = "Hit"),

	// 防御
	Defense = 5 UMETA(DisplayName = "Defense")
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

/**
 *
 */
class BTD_API GameEnums
{
public:
	GameEnums();
	~GameEnums();
};
