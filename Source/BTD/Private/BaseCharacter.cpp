// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Interface/IActorProperty.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Module/FMovingModule.h"
#include "Module/FRotationModule.h"
#include "Module/DataModule.h"
#include "Module/FStateMachineModule.h"
#include "StateMachine/FActionsState.h"
#include "StateMachine/FCombatState.h"
#include "StateMachine/FMovingState.h"
#include "StateMachine/FTopState.h"


ABaseCharacter::ABaseCharacter()
{
	// 初始化数据模块
	CharacterDataModule = new DataModule();
	// 初始化状态机模块
	StateMachineModule = new FStateMachineModule(this, this, CharacterDataModule);
	// 初始化动画实例指针
	BaseAnimation = nullptr;
	// 初始化目标旋转方向
	TargetRotationDirection = FVector::ZeroVector;

	//初始化不同角度范围的旋转速度（0-45°, 45-90°, 90-135°, 135-180°）
	AngleRangeRotationSpeeds.Add(0.2f); // 0-45度：较快
	AngleRangeRotationSpeeds.Add(0.18f); // 45-90度：中等
	AngleRangeRotationSpeeds.Add(0.16f); // 90-135度：较慢
	AngleRangeRotationSpeeds.Add(0.13f); // 135-180度：最慢


	// 初始化 ActorRotation，传入自身作为 IIHolderAttribute 接口
	RotationModule = new FRotationModule(this, StateMachineModule);
	// 初始化 MovingModule，传入自身作为 IIHolderAttribute 接口
	MovingModule = new FMovingModule(this, StateMachineModule);
}


ABaseCharacter::~ABaseCharacter()
{
	delete StateMachineModule;
	StateMachineModule = nullptr;
	delete CharacterDataModule;
	CharacterDataModule = nullptr;
	delete RotationModule;
	RotationModule = nullptr;
	delete MovingModule;
	MovingModule = nullptr;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 从骨骼网格组件获取动画实例
	BaseAnimation = Cast<UFBaseAnimation>(GetMesh()->GetAnimInstance());

	// 将动画实例的状态设置方法注册到状态机模块的委托
	if (BaseAnimation)
	{
		StateMachineModule->OnTopStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchTopState);
		StateMachineModule->OnCombatStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchCombatState);
		StateMachineModule->OnActionsStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchBehaviourState);
		StateMachineModule->OnMovingStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchMoveState);
		StateMachineModule->OnRotationStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchRotationType);
		StateMachineModule->OnWeaponStateChanged.AddUObject(BaseAnimation, &UFBaseAnimation::SwitchCombatType);
	}

	RotationModule->InitRotationModel(AngleRangeRotationSpeeds); //旋转模块初始化
	// 设置起始移动状态为行走
	SetMoveState(EMoveState::Walking);
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移动模块更新（现在只更新了 移动方向，移动的具体操作由AIMove执行）
	MovingModule->MovingModuleTick(DeltaTime);
	//转向模块更新
	RotationModule->RotationModuleTick();
	// 状态机模块更新
	StateMachineModule->Tick(DeltaTime);
}

/*SetupPlayerInputComponent 是 UE 的 APawn 基类提供的虚函数，专门用于绑定玩家输入。
调用时机： 当玩家控制器（PlayerController）接管该 Pawn 时，引擎自动调用一次。 */
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*移动流程 开始*/
void ABaseCharacter::SetMoveState(const EMoveState InMoveState)
{
	// 根据状态赋值当前移动速度
	StateMachineModule->SwitchMovingState(InMoveState);
}


void ABaseCharacter::BeginActiveMove()
{
	// 设置行为状态为移动
	StateMachineModule->SwitchActionsState(ECharacterBehavior::Moving);
}


void ABaseCharacter::OnMoveEnd()
{
	// 重置行为状态为闲置
	StateMachineModule->SwitchActionsState(ECharacterBehavior::Idle);
}

void ABaseCharacter::SetTargetActor(ABaseCharacter* InTargetActor)
{
	if (!InTargetActor)
		return;
	StateMachineModule->SwitchCombatState(ECombatState::Combat);
	TargetActor = InTargetActor;
}

/*移动流程 结束*/

/*蓝图调用 转向相关 start */
void ABaseCharacter::ActivateRotating_Implementation()
{
	StateMachineModule->SwitchCombatState(ECombatState::Idle);
	StateMachineModule->SwitchRotationState(EActorRotaType::Rotating);
}

void ABaseCharacter::ActiveGazing_Implementation()
{
	// 检查TargetActor是否有效
	if (!TargetActor || !TargetActor->Implements<UIHolderFunction>())
	{
		return;
	}
	StateMachineModule->SwitchRotationState(EActorRotaType::Gazing);
}

/*蓝图调用 转向相关 end */


/*接口实现 Start*/
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
	//通过 IIActorProperty 接口获取目标角色的位置
	//使用 IsValid 确保 TargetActor 未被销毁（避免悬空指针崩溃）
	if (IsValid(TargetActor) && TargetActor->Implements<UIHolderAttribute>())
	{
		return TargetActor->GetActorLocation();
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

FVector ABaseCharacter::GetTargetRotationDirection_Implementation() const
{
	// 返回当前角色的目标旋转方向
	return TargetRotationDirection;
}

void ABaseCharacter::SetTargetRotationDirection_Implementation(const FVector& NewDirection)
{
	// 设置当前角色的目标旋转方向
	TargetRotationDirection = NewDirection;
}

//设置移动速度
void ABaseCharacter::SetMovementSpeed_Implementation(const float Value)
{
	// 将当前移动速度赋值给移动组件
	GetCharacterMovement()->MaxWalkSpeed = Value;
}
