// Fill out your copyright notice in the Description page of Project Settings.


#include "Module/InstructionCacheModule/FActionInstruction.h"

FActionInstruction::FActionInstruction()
	: CacheDuration(0.0f)
	, ExecuteDuration(0.0f)
	, StartTime(0.0f)
	, ExecuteTargetTime(0.0f)
	, CacheExpireTime(0.0f)
	, EnqueueTime(0.0f)
	, bIsExecuting(false)
	, bTimerTickFired(false)
{
}

FActionInstruction::~FActionInstruction()
{
	Cleanup();
}

void FActionInstruction::Initialize(float InCacheDuration, float InExecuteDuration)
{
	CacheDuration = InCacheDuration;
	ExecuteDuration = InExecuteDuration;
}

void FActionInstruction::Cleanup()
{
	OnStarted.Clear();
	OnFinished.Clear();
	OnInterrupted.Clear();
	OnTimerTick.Clear();
}

void FActionInstruction::StartExecute(float CurrentTime)
{
	StartTime = CurrentTime;
	ExecuteTargetTime = StartTime + ExecuteDuration;
	CacheExpireTime = StartTime + CacheDuration;
	bIsExecuting = true;
	bTimerTickFired = false;
	NotifyStarted();
}

void FActionInstruction::InterruptExecute()
{
	if (!bIsExecuting)
	{
		return;
	}
	bIsExecuting = false;
	NotifyInterrupted();
}

void FActionInstruction::Tick(float CurrentTime)
{
	if (!bIsExecuting)
	{
		return;
	}

	// 到达执行时间节点，触发计时事件（每次执行周期只触发一次）
	if (!bTimerTickFired && CurrentTime >= ExecuteTargetTime)
	{
		bTimerTickFired = true;
		NotifyTimerTick(CurrentTime);
	}

	// 到达缓存过期时间节点，触发完成事件
	if (CurrentTime >= CacheExpireTime)
	{
		bIsExecuting = false;
		NotifyFinished();
	}
}

void FActionInstruction::NotifyStarted()
{
	OnStarted.Broadcast();
}

void FActionInstruction::NotifyFinished()
{
	OnFinished.Broadcast();
}

void FActionInstruction::NotifyInterrupted()
{
	OnInterrupted.Broadcast();
}

void FActionInstruction::NotifyTimerTick(float ElapsedTime)
{
	OnTimerTick.Broadcast(ElapsedTime);
}

FDelegateHandle FActionInstruction::RegisterOnStarted(const FOnInstructionStarted::FDelegate& Delegate)
{
	return OnStarted.Add(Delegate);
}

void FActionInstruction::UnregisterOnStarted(FDelegateHandle Handle)
{
	OnStarted.Remove(Handle);
}

FDelegateHandle FActionInstruction::RegisterOnFinished(const FOnInstructionFinished::FDelegate& Delegate)
{
	return OnFinished.Add(Delegate);
}

void FActionInstruction::UnregisterOnFinished(FDelegateHandle Handle)
{
	OnFinished.Remove(Handle);
}

FDelegateHandle FActionInstruction::RegisterOnInterrupted(const FOnInstructionInterrupted::FDelegate& Delegate)
{
	return OnInterrupted.Add(Delegate);
}

void FActionInstruction::UnregisterOnInterrupted(FDelegateHandle Handle)
{
	OnInterrupted.Remove(Handle);
}

FDelegateHandle FActionInstruction::RegisterOnTimerTick(const FOnInstructionTimerTick::FDelegate& Delegate)
{
	return OnTimerTick.Add(Delegate);
}

void FActionInstruction::UnregisterOnTimerTick(FDelegateHandle Handle)
{
	OnTimerTick.Remove(Handle);
}
