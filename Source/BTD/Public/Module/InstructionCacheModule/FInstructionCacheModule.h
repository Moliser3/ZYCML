// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDataStruct.h"
#include "Module/InstructionCacheModule/FActionInstruction.h"

/**
 * 行动指令缓存模块
 * 队列存储轻便技能指令，出队时才构建完整 FActionInstruction 并执行
 */
class BTD_API FInstructionCacheModule
{
public:
	FInstructionCacheModule();
	~FInstructionCacheModule();

	// 输入新的轻便指令：若当前有指令执行则入队，否则立即构建并执行
	void InputInstruction(const FLightSkillInstruction& InSkillInstruction, float CurrentTime);

	// 每帧驱动：更新当前指令 / 从队列取下一条 / 清理过期缓存
	void Tick(float CurrentTime);

private:
	// 从缓存队列中取出下一条有效指令，构建后开始执行
	void TryDequeueNext(float CurrentTime);

	// 通过轻便指令构建完整 FActionInstruction 并开始执行
	void BuildAndExecute(const FLightSkillInstruction& InSkillInstruction, float CurrentTime);

	// 当前正在执行的指令
	TSharedPtr<FActionInstruction> ActiveInstruction;

	// 等待执行的轻便指令缓存队列（先进先出）
	// 每条缓存项：轻便指令 + 入队时间戳
	TQueue<TTuple<FLightSkillInstruction, float>> InstructionQueue;
};
