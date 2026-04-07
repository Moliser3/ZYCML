// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 指令开始执行委托
DECLARE_MULTICAST_DELEGATE(FOnInstructionStarted);
// 指令执行结束委托
DECLARE_MULTICAST_DELEGATE(FOnInstructionFinished);
// 指令被打断委托
DECLARE_MULTICAST_DELEGATE(FOnInstructionInterrupted);
// 指令计时触发委托（触发时已经过的时间）
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInstructionTimerTick, float);

/**
 * 行动指令类
 * 包含指令缓存时间、执行时间，以及开始/结束/被打断/计时触发四个事件回调
 */
class BTD_API FActionInstruction
{
public:
	FActionInstruction();
	~FActionInstruction();

	// 初始化指令，设置缓存时间和执行时间
	void Initialize(float InCacheDuration, float InExecuteDuration);
	// 清理所有委托绑定
	void Cleanup();

	// 开始执行指令，传入当前游戏时间，计算目标时间戳并广播开始事件
	void StartExecute(float CurrentTime);
	// 打断执行指令，停止计时并广播打断事件
	void InterruptExecute();
	// Tick 驱动计时，传入当前游戏时间，到达执行时间触发计时事件，到达缓存生命周期触发完成事件
	void Tick(float CurrentTime);

	// 触发指令开始
	void NotifyStarted();
	// 触发指令结束
	void NotifyFinished();
	// 触发指令被打断
	void NotifyInterrupted();
	// 触发计时回调
	void NotifyTimerTick(float ElapsedTime);

	// 注册/注销指令开始事件
	FDelegateHandle RegisterOnStarted(const FOnInstructionStarted::FDelegate& Delegate);
	void UnregisterOnStarted(FDelegateHandle Handle);

	// 注册/注销指令结束事件
	FDelegateHandle RegisterOnFinished(const FOnInstructionFinished::FDelegate& Delegate);
	void UnregisterOnFinished(FDelegateHandle Handle);

	// 注册/注销指令被打断事件
	FDelegateHandle RegisterOnInterrupted(const FOnInstructionInterrupted::FDelegate& Delegate);
	void UnregisterOnInterrupted(FDelegateHandle Handle);

	// 注册/注销计时触发事件
	FDelegateHandle RegisterOnTimerTick(const FOnInstructionTimerTick::FDelegate& Delegate);
	void UnregisterOnTimerTick(FDelegateHandle Handle);

	// 记录入队时间，用于缓存过期判断
	void SetEnqueueTime(float InEnqueueTime) { EnqueueTime = InEnqueueTime; }
	// 判断当前时间是否已超出缓存等待期（入队时间 + 缓存时间）
	bool IsCacheExpired(float CurrentTime) const { return CurrentTime >= EnqueueTime + CacheDuration; }

	// 获取指令缓存时间（秒）
	float GetCacheDuration() const { return CacheDuration; }
	// 获取指令执行时间（秒）
	float GetExecuteDuration() const { return ExecuteDuration; }
	// 是否正在执行
	bool IsExecuting() const { return bIsExecuting; }

private:
	// 指令缓存时间（秒）
	float CacheDuration;
	// 指令执行时间（秒）
	float ExecuteDuration;
	// 指令开始时的游戏时间戳（秒）
	float StartTime;
	// 计时触发事件的目标时间戳：StartTime + ExecuteDuration
	float ExecuteTargetTime;
	// 缓存清理的目标时间戳：StartTime + CacheDuration
	float CacheExpireTime;
	// 指令入队时的游戏时间戳，用于在出队前判断缓存是否过期
	float EnqueueTime;
	// 是否正在执行
	bool bIsExecuting;
	// 计时触发事件是否已触发（每次执行周期内只触发一次）
	bool bTimerTickFired;

	// 指令开始执行委托
	FOnInstructionStarted OnStarted;
	// 指令执行结束委托
	FOnInstructionFinished OnFinished;
	// 指令被打断委托
	FOnInstructionInterrupted OnInterrupted;
	// 计时触发委托
	FOnInstructionTimerTick OnTimerTick;
};
