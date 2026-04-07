// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDataStruct.h"

/**
 * 行动指令对象，持有轻便技能指令数据
 */
class BTD_API FActionInstructionObject
{
public:
	FActionInstructionObject() = default;
	explicit FActionInstructionObject(const FLightSkillInstruction& InSkillInstruction);

	// 轻便技能指令数据
	FLightSkillInstruction SkillInstruction;
};
