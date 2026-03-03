// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationData.h"
#include "NavigationSystem.h"


ABaseCharacter::ABaseCharacter()
{
	// 初始化旋转状态
	CurrentRotaType = EActorRotaType::Default;
	CurrentRotationSpeed = 0.1f;
	TargetRotatePosition = FVector::ZeroVector;

	// 初始化移动状态
	CurrentMoveState = EMoveState::Idle;

	// 初始化移动状态检查计时器
	MoveStateCheckTimer = 0.0f;
	LastRecordedPosition = FVector::ZeroVector;

	// 初始化移动状态检查间隔时间
	MoveStateCheckInterval = 0.1f;

	// 初始化旋转速度
	RotationSpeed = 0.1f;

	// 初始化目标旋转方向
	TargetRotationDirection = FVector::ZeroVector;

	// 初始化不同角度范围的旋转速度（0-45°, 45-90°, 90-135°, 135-180°）
	AngleRangeRotationSpeeds.Add(0.2f);  // 0-45度：较快
	AngleRangeRotationSpeeds.Add(0.15f); // 45-90度：中等
	AngleRangeRotationSpeeds.Add(0.1f);  // 90-135度：较慢
	AngleRangeRotationSpeeds.Add(0.05f); // 135-180度：最慢

	// 初始化角色类型（默认为主角）
	CharacterType = ECharacterType::Player;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 先检查移动状态（更新位置）
	CheckMoveState(DeltaTime);

	// 再更新旋转状态
	UpdateRotation();
}


void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::RotateToTargeDirection(const FVector& TargetDirection, float InRotationSpeed)
{
	// 规范化目标方向向量（仅使用X、Y平面，忽略Z轴）
	FVector NormalizedDirection = TargetDirection;
	NormalizedDirection.Z = 0.0f; // 清零Z轴分量，确保只在水平面上旋转
	NormalizedDirection.Normalize(); // 归一化方向向量

	// 处理零向量的情况
	if (!NormalizedDirection.IsNormalized())
	{
		return; // 如果无法计算有效方向，则不进行旋转
	}

	// 获取当前Forward向量
	FVector CurrentForward = GetActorForwardVector();
	CurrentForward.Z = 0.0f;
	CurrentForward.Normalize();

	// 计算当前Forward和目标方向的夹角
	float DotProduct = FVector::DotProduct(CurrentForward, NormalizedDirection);
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);

	// 根据夹角范围选择对应的旋转速度
	float FinalRotationSpeed = InRotationSpeed;
	if (AngleRangeRotationSpeeds.Num() >= 4)
	{
		if (AngleDifference < 45.0f)
		{
			FinalRotationSpeed = AngleRangeRotationSpeeds[0]; // 0-45度
		}
		else if (AngleDifference < 90.0f)
		{
			FinalRotationSpeed = AngleRangeRotationSpeeds[1]; // 45-90度
		}
		else if (AngleDifference < 135.0f)
		{
			FinalRotationSpeed = AngleRangeRotationSpeeds[2]; // 90-135度
		}
		else
		{
			FinalRotationSpeed = AngleRangeRotationSpeeds[3]; // 135-180度
		}
	}

	// 获取当前旋转信息
	FRotator CurrentRotation = GetActorRotation();
	float CurrentYaw = CurrentRotation.Yaw;

	// 计算目标方向相对于世界坐标系的Yaw角度
	float TargetYaw = FMath::Atan2(NormalizedDirection.Y, NormalizedDirection.X) * (180.0f / PI);

	// 计算旋转差值
	float YawDelta = TargetYaw - CurrentYaw;

	// 选择最短旋转路径（-180到180之间）
	if (YawDelta > 180.0f)
	{
		YawDelta -= 360.0f;
	}
	else if (YawDelta < -180.0f)
	{
		YawDelta += 360.0f;
	}

	// 使用Lerp进行平滑旋转
	float NewYaw = FMath::Lerp(CurrentYaw, CurrentYaw + YawDelta, FinalRotationSpeed);

	// 应用新的旋转
	FRotator NewRotation = CurrentRotation;
	NewRotation.Yaw = NewYaw;
	SetActorRotation(NewRotation);
}

void ABaseCharacter::ActivateRotation(const FVector& InTargetDirection)
{
	// 激活旋转状态
	CurrentRotaType = EActorRotaType::Rotating;

	// 保存目标方向和旋转速度
	TargetRotationDirection = InTargetDirection;
	CurrentRotationSpeed = FMath::Clamp(RotationSpeed, 0.0f, 1.0f); // 使用蓝图变量，限制速度在0-1之间
}

void ABaseCharacter::UpdateRotation()
{
	// 如果旋转状态不是默认状态，执行旋转更新
	if (CurrentRotaType != EActorRotaType::Default)
	{
		RotateToTargeDirection(TargetRotationDirection, CurrentRotationSpeed);

		// 检测旋转是否完成
		CheckRotationCompletion();
	}
}

void ABaseCharacter::CheckRotationCompletion()
{
	// 如果无法计算有效方向，则不进行检测
	if (!TargetRotationDirection.IsNormalized())
	{
		return;
	}

	// 获取当前角色的Forward向量（仅X、Y平面）
	FVector CurrentForward = GetActorForwardVector();
	CurrentForward.Z = 0.0f;
	CurrentForward.Normalize();

	// 输出旋转目标方向（基于CheckMoveState时保存的方向）
	UE_LOG(LogTemp, Display, TEXT("旋转目标方向 - DirectionToTarget: (X=%.2f, Y=%.2f, Z=%.2f)"), TargetRotationDirection.X, TargetRotationDirection.Y, TargetRotationDirection.Z);

	// 计算两个向量之间的夹角
	float DotProduct = FVector::DotProduct(CurrentForward, TargetRotationDirection);
	// 夹角值范围在-1到1之间，Clamp确保不会有浮点误差导致的异常
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);

	// 如果夹角小于阈值，说明Forward向量已经指向目标方向，停止旋转
	if (AngleDifference < RotationCompletionThreshold)
	{
		CurrentRotaType = EActorRotaType::Default;
	}
}

void ABaseCharacter::ActiveMove(EMoveState InMoveState)
{
	// 激活角色的移动状态
	CurrentMoveState = InMoveState;

	// 当激活为空闲状态时，重置相关参数
	if (InMoveState == EMoveState::Idle)
	{
		MoveStateCheckTimer = 0.0f;

		// 只有当不在旋转状态时，才重置目标旋转方向
		if (CurrentRotaType == EActorRotaType::Default)
		{
			TargetRotationDirection = FVector::ZeroVector;
		}
	}
}

void ABaseCharacter::SetRotaType(EActorRotaType InRotaType)
{
	// 直接设置旋转状态
	CurrentRotaType = InRotaType;

	// 如果设置为默认状态，清空旋转目标方向
	if (InRotaType == EActorRotaType::Default)
	{
		TargetRotationDirection = FVector::ZeroVector;
	}
}

void ABaseCharacter::CheckMoveState(float DeltaTime)
{
	// 如果状态为空闲，停止后续逻辑
	if (CurrentMoveState == EMoveState::Idle)
	{
		return;
	}

	// 累计检查计时器
	MoveStateCheckTimer += DeltaTime;

	// 当计时器达到检查间隔时，进行一次检查
	if (MoveStateCheckTimer >= MoveStateCheckInterval)
	{
		// 获取当前角色位置
		FVector CurrentLocation = GetActorLocation();

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
		FVector CurrentForward = GetActorForwardVector();
		CurrentForward.Z = 0.0f;
		CurrentForward.Normalize();

		// 计算移动方向与Forward向量之间的夹角
		float DotProduct = FVector::DotProduct(CurrentForward, MoveDirection);
		DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
		float AngleDifference = FMath::Acos(DotProduct) * (180.0f / PI);

		// 如果夹角过大（超过10度），则调用旋转方法调整朝向
		// 10度的阈值确保只有明显偏离时才会触发旋转
		const float DirectionMismatchThreshold = 10.0f;
		if (AngleDifference > DirectionMismatchThreshold)
		{
			// 判断是否已经在旋转，只有当不在旋转状态时才启动新的旋转
			if (CurrentRotaType == EActorRotaType::Default)
			{
				// 调用旋转方法，直接传入移动方向
				// 旋转速度使用蓝图可编辑的 RotationSpeed 变量
				ActivateRotation(MoveDirection);
			}
		}
	}
}
