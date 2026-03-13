// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "ActorRotation.h"
#include "Interface/IActorProperty.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseCharacter::ABaseCharacter()
{
	// 初始化旋转状态
	CurrentRotaType = EActorRotaType::Default;
	CurrentRotationSpeed = 0.1f;
	TargetRotatePosition = FVector::ZeroVector;

	// 初始化移动状态
	CurrentMoveState = EMoveState::Walking;

	// 初始化当前移动速度
	CurrentMoveSpeed = 0.f;

	// 初始化移动状态检查计时器
	MoveStateCheckTimer = 0.0f;
	LastRecordedPosition = FVector::ZeroVector;

	// 初始化移动状态检查间隔时间
	MoveStateCheckInterval = 0.1f;

	// 初始化旋转速度
	RotationSpeed = 0.1f;

	// 初始化目标旋转方向
	TargetRotationDirection = FVector::ZeroVector;

	//初始化不同角度范围的旋转速度（0-45°, 45-90°, 90-135°, 135-180°）
	AngleRangeRotationSpeeds.Add(0.2f); // 0-45度：较快
	AngleRangeRotationSpeeds.Add(0.18f); // 45-90度：中等
	AngleRangeRotationSpeeds.Add(0.16f); // 90-135度：较慢
	AngleRangeRotationSpeeds.Add(0.13f); // 135-180度：最慢

	// 初始化角色类型（默认为主角）
	CharacterType = ECharacterType::Player;


	// 初始化 ActorRotation，传入自身作为 IIHolderAttribute 接口
	ActorRotationModule = new ActorRotation(this);
}


ABaseCharacter::~ABaseCharacter()
{
	delete ActorRotationModule;
	ActorRotationModule = nullptr;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActorRotationModule->InitModel(AngleRangeRotationSpeeds); //旋转模块初始化
	// 设置起始移动状态为行走
	SetMoveState(EMoveState::Walking);
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 先检查移动状态（更新位置）
	CheckMoveState(DeltaTime);

	// 再更新旋转状态
	//UpdateRotation();
	//转向模块更新
	ActorRotationModule->RotationTick();
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::ActivateRotation(const FVector& InTargetDirection)
{
	// 激活旋转状态
	CurrentRotaType = EActorRotaType::Rotating;

	// 保存目标方向和旋转速度
	TargetRotationDirection = InTargetDirection;
	CurrentRotationSpeed = FMath::Clamp(RotationSpeed, 0.0f, 1.0f); // 使用蓝图变量，限制速度在0-1之间
}


void ABaseCharacter::BeginActiveMove()
{
	// 设置行为状态为移动
	SetBehavior(ECharacterBehavior::Moving);

	// 将当前移动速度赋值给移动组件
	GetCharacterMovement()->MaxWalkSpeed = CurrentMoveSpeed;
	switch (CurrentMoveState)
	{
	case EMoveState::Walking:
		break;
	case EMoveState::Running:
		if (CurrentRotaType == EActorRotaType::Gazing && CurrentMoveState == EMoveState::Walking)
		{
			break;
		}
		ActiveRota();
		break;
	default: ;
	}
	// // 当激活为空闲状态时，重置相关参数
	// if (InMoveState == EMoveState::Idle)
	// {
	// 	MoveStateCheckTimer = 0.0f;
	//
	// 	// 只有当不在旋转状态时，才重置目标旋转方向
	// 	if (CurrentRotaType == EActorRotaType::Default)
	// 	{
	// 		TargetRotationDirection = FVector::ZeroVector;
	// 	}
	// }
}

void ABaseCharacter::SetMoveState(EMoveState InMoveState)
{
	// 切换移动状态枚举
	//ActiveMove(InMoveState);

	// 根据状态赋值当前移动速度
	switch (InMoveState)
	{
	case EMoveState::Walking:
		CurrentMoveSpeed = CharacterData.WalkSpeed;
		CurrentMoveState = EMoveState::Walking;
		break;
	case EMoveState::Running:
		CurrentMoveSpeed = CharacterData.RunSpeed;
		CurrentMoveState = EMoveState::Running;
		break;
	default:
		break;
	}
}


void ABaseCharacter::ActivateRunning()
{
	SetMoveState(EMoveState::Running);
}

void ABaseCharacter::ActivateWalking()
{
	SetMoveState(EMoveState::Walking);
}

void ABaseCharacter::ActiveRota()
{
	CurrentRotaType = EActorRotaType::Rotating;
}

void ABaseCharacter::ActiveGazing()
{
	// 检查TargetActor是否有效
	if (!TargetActor || !TargetActor->Implements<UIActorProperty>())
	{
		return;
	}

	// 设置旋转状态为Gazing
	CurrentRotaType = EActorRotaType::Gazing;
}

void ABaseCharacter::CheckMoveState(float DeltaTime)
{
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

void ABaseCharacter::OnMoveEnd()
{
	// 重置行为状态为闲置
	SetBehavior(ECharacterBehavior::Idle);
}

void ABaseCharacter::SetBehavior(ECharacterBehavior NewBehavior)
{
	if (CurrentBehavior != NewBehavior)
		CurrentBehavior = NewBehavior;
	OnBehaviorChanged.Broadcast(CurrentBehavior, CurrentMoveState);
}

FVector ABaseCharacter::GetLocation_Implementation() const
{
	// 返回当前角色的位置
	return GetActorLocation();
}

FVector ABaseCharacter::GetForwardVector_Implementation() const
{
	// 返回当前角色的正方向向量
	return GetActorForwardVector();
}

FVector ABaseCharacter::GetTargetLocation_Implementation() const
{
	// 通过 IIActorProperty 接口获取目标角色的位置
	// 使用 IsValid 确保 TargetActor 未被销毁（避免悬空指针崩溃）
	if (IsValid(TargetActor) && TargetActor->Implements<UIActorProperty>())
	{
		return IIActorProperty::Execute_GetLocation(TargetActor);
	}
	return FVector::ZeroVector;
}

FRotator ABaseCharacter::GetRotation_Implementation() const
{
	// 返回当前角色的旋转角度
	return GetActorRotation();
}

void ABaseCharacter::SetHolderRotation_Implementation(FRotator NewRotation)
{
	// 设置当前角色的旋转角度
	SetActorRotation(NewRotation);
}

EActorRotaType ABaseCharacter::GetCurrentRotaType_Implementation() const
{
	// 返回当前角色的旋转类型状态
	return CurrentRotaType;
}

void ABaseCharacter::SetCurrentRotaType_Implementation(EActorRotaType NewRotaType)
{
	// 设置当前角色的旋转类型状态
	CurrentRotaType = NewRotaType;
}

FVector ABaseCharacter::GetTargetRotationDirection_Implementation() const
{
	// 返回当前角色的目标旋转方向
	return TargetRotationDirection;
}
