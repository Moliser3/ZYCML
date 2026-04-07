// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEnums.h"
#include "CharacterDataStruct.generated.h"

// 角色数据结构体
USTRUCT(BlueprintType)
struct BTD_API FCharacterData
{
    GENERATED_BODY()

    // 血量
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
    float Health;

    // 能量
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
    float Energy;

    // 走路速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
    float WalkSpeed;

    // 奔跑速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
    float RunSpeed;

    FCharacterData()
        : Health(100.f)
        , Energy(100.f)
        , WalkSpeed(300.f)
        , RunSpeed(600.f)
    {
    }
};
// 轻便技能指令结构体
USTRUCT(BlueprintType)
struct BTD_API FLightSkillInstruction
{
    GENERATED_BODY()

    // 战斗类型
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInstruction")
    ECombatType Combat;

    // 技能名称
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInstruction")
    FName Skill;

    // 技能索引
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInstruction")
    int32 SkillIndex;

    // 持续时间（秒）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInstruction")
    float DurationTime;

    FLightSkillInstruction()
        : Combat(ECombatType::Boxing)
        , Skill(NAME_None)
        , SkillIndex(0)
        , DurationTime(0.0f)
    {
    }
};


/**
 *
 */
class BTD_API CharacterDataStruct
{
public:
    CharacterDataStruct();
    ~CharacterDataStruct();
};
