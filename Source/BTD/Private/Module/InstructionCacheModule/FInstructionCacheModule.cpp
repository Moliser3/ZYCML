// Fill out your copyright notice in the Description page of Project Settings.

#include "Module/InstructionCacheModule/FInstructionCacheModule.h"

FInstructionCacheModule::FInstructionCacheModule()
{
}

FInstructionCacheModule::~FInstructionCacheModule()
{
}

void FInstructionCacheModule::InputInstruction(const FLightSkillInstruction& InSkillInstruction, float CurrentTime)
{
	// 有指令正在执行，将轻便指令连同入队时间戳一起缓存
	if (ActiveInstruction.IsValid() && ActiveInstruction->IsExecuting())
	{
		InstructionQueue.Enqueue(MakeTuple(InSkillInstruction, CurrentTime));
		return;
	}

	// 无指令执行，直接构建并执行
	BuildAndExecute(InSkillInstruction, CurrentTime);
}

void FInstructionCacheModule::Tick(float CurrentTime)
{
	// 当前有指令正在执行，驱动其 Tick
	if (ActiveInstruction.IsValid() && ActiveInstruction->IsExecuting())
	{
		ActiveInstruction->Tick(CurrentTime);
		return;
	}

	// 当前无执行中的指令，尝试从队列取下一条
	TryDequeueNext(CurrentTime);
}

void FInstructionCacheModule::TryDequeueNext(float CurrentTime)
{
	TTuple<FLightSkillInstruction, float> Item;

	// 逐条检查队列头部，清理已过期的缓存指令，找到第一条有效的立即执行
	while (InstructionQueue.Dequeue(Item))
	{
		const FLightSkillInstruction& SkillInstruction = Item.Get<0>();
		const float EnqueueTime = Item.Get<1>();

		// 入队时间 + 缓存时间 <= 当前时间，说明已过期，丢弃
		if (CurrentTime >= EnqueueTime + SkillInstruction.DurationTime)
		{
			continue;
		}

		// 找到有效指令，构建并执行
		BuildAndExecute(SkillInstruction, CurrentTime);
		return;
	}

	// 队列已空
	ActiveInstruction.Reset();
}

void FInstructionCacheModule::BuildAndExecute(const FLightSkillInstruction& InSkillInstruction, float CurrentTime)
{
	TSharedPtr<FActionInstruction> Instruction = MakeShared<FActionInstruction>();
	Instruction->Initialize(InSkillInstruction.DurationTime, InSkillInstruction.DurationTime);
	ActiveInstruction = Instruction;
	ActiveInstruction->StartExecute(CurrentTime);
}
