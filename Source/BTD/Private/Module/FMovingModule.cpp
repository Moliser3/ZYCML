// Fill out your copyright notice in the Description page of Project Settings.


#include "Module/FMovingModule.h"
#include "GameEnums.h"
FMovingModule::FMovingModule(IIHolderAttribute* InHolder, IIHolderStateMachine* InHolderM): HolderAttribute(InHolder), HolderStateMachine(InHolderM)
{
	// 初始化移动状态检查计时器
	MoveStateCheckTimer = 0.0f;
	// 初始化移动状态检查的时间间隔（秒）
	MoveStateCheckInterval = 0.05f;
	// 初始化最后位置
	LastRecordedPosition = FVector::Zero();
	// 初始化移动方向
	CurrentMoveDirection = EMoveDirection::Forward;


}

FMovingModule::~FMovingModule()
{
}

FDelegateHandle FMovingModule::RegisterMoveDirectionChanged(const FOnGazingMoveDirectionChanged::FDelegate& Delegate)
{
	return OnGazingMoveDirectionChanged.Add(Delegate);
}

void FMovingModule::UnregisterMoveDirectionChanged(FDelegateHandle Handle)
{
	OnGazingMoveDirectionChanged.Remove(Handle);
}

// 检查移动状态，根据移动方向调整角色朝向
void FMovingModule::MovingModuleTick(float DeltaTime)
{
	if (HolderStateMachine->GetActionsState() != ECharacterBehavior::Moving)
		return;
	// 累计检查计时器
	MoveStateCheckTimer += DeltaTime;

	// 当计时器达到检查间隔时，进行一次检查
	if (MoveStateCheckTimer >= MoveStateCheckInterval)
	{
		// 获取当前角色位置
		const FVector CurrentLocation = HolderAttribute->GetLocation_Implementation();

		// 首次记录时，初始化上一次位置
		if (LastRecordedPosition.IsZero())
		{
			LastRecordedPosition = CurrentLocation;
			MoveStateCheckTimer = 0.0f;
			return;
		}

		// 计算移动方向（从上一个位置到当前位置）
		FVector MoveDirection = (CurrentLocation - LastRecordedPosition);
		MoveDirection.Z = 0.0f; // 只考虑水平平面的移动
		MoveDirection.Normalize(); // 归一化方向向量

		// 更新上一次记录的位置
		LastRecordedPosition = CurrentLocation;

		// 重置计时器
		MoveStateCheckTimer = 0.0f;

		// 如果无法计算有效方向，则不进行旋转
		if (!MoveDirection.IsNormalized())
		{
			return;
		}

		// 获取当前角色的Forward向量（仅水平面）
		FVector CurrentForward = HolderAttribute->GetForwardVector_Implementation();
		CurrentForward.Z = 0.0f;
		CurrentForward.Normalize();

		// 计算移动方向与Forward向量之间的夹角
		float DotProduct = FVector::DotProduct(CurrentForward, MoveDirection);
		DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
		float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);
		// 注视模式：计算当前帧的移动方向（前/后/左/右）
		if (HolderStateMachine->GetRotationState() == EActorRotaType::Gazing)
		{
			// 右向量 = Cross(Up, Forward)，即 (-fy, fx, 0)
			const FVector RightVector = FVector(-CurrentForward.Y, CurrentForward.X, 0.0f);
			const float ForwardDot = FVector::DotProduct(MoveDirection, CurrentForward);
			const float RightDot = FVector::DotProduct(MoveDirection, RightVector);

			EMoveDirection NewDirection;
			if (FMath::Abs(ForwardDot) >= FMath::Abs(RightDot))
			{
				NewDirection = ForwardDot >= 0.0f ? EMoveDirection::Forward : EMoveDirection::Backward;
			}
			else
			{
				NewDirection = RightDot >= 0.0f ? EMoveDirection::Right : EMoveDirection::Left;
			}

			if (NewDirection != CurrentMoveDirection)
			{
				CurrentMoveDirection = NewDirection;
				OnGazingMoveDirectionChanged.Broadcast(CurrentMoveDirection);
			}
			return;
		}

		// 旋转模式：如果夹角过大（超过5度），调整角色朝向
		if (constexpr float DirectionMismatchThreshold = 5.0f; AngleDifference > DirectionMismatchThreshold)
		{
			//设置 当前旋转模式
			HolderAttribute->SetCurrentRotaType_Implementation(EActorRotaType::Rotating);
			//设置 移动方向
			HolderAttribute->SetTargetRotationDirection_Implementation(MoveDirection);
		}
	}
}
