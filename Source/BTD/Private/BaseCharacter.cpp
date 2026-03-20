// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Interface/IActorProperty.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Module/FMovingModule.h"
#include "Module/FRotationModule.h"
#include "StateMachine/FActionsState.h"
#include "StateMachine/FActionsStateMachine.h"
#include "StateMachine/FCombatState.h"
#include "StateMachine/FCombatStateMachine.h"
#include "StateMachine/FMovingState.h"
#include "StateMachine/FMovingStateMachine.h"
#include "StateMachine/FTopState.h"
#include "StateMachine/FTopStateMachine.h"


ABaseCharacter::ABaseCharacter()
{
    // 初始化动画实例指针
    BaseAnimation = nullptr;

    // 初始化旋转状态
    CurrentRotaType = EActorRotaType::Rotating;

    // 初始化移动状态
    CurrentMoveState = EMoveState::Walking;

    // 初始化当前移动速度
    CurrentMoveSpeed = 0.f;

    // 初始化目标旋转方向
    TargetRotationDirection = FVector::ZeroVector;

    //初始化不同角度范围的旋转速度（0-45°, 45-90°, 90-135°, 135-180°）
    AngleRangeRotationSpeeds.Add(0.2f); // 0-45度：较快
    AngleRangeRotationSpeeds.Add(0.18f); // 45-90度：中等
    AngleRangeRotationSpeeds.Add(0.16f); // 90-135度：较慢
    AngleRangeRotationSpeeds.Add(0.13f); // 135-180度：最慢

    // 初始化角色类型（默认为主角）
    CharacterType = ECharacterType::Player;

    // 初始化战斗类型（默认为拳击）
    CurrentCombatType = ECombatType::Boxing;

    // 初始化角色状态（默认为闲置）
    CurrentCharacterState = ECombatState::Idle;

    // 初始化 ActorRotation，传入自身作为 IIHolderAttribute 接口
    RotationModule = new FRotationModule(this);
    // 初始化 MovingModule，传入自身作为 IIHolderAttribute 接口
    MovingModule = new FMovingModule(this);

    /*状态机-初始化*/
    //一级状态
    TopStateMachine = new FTopStateMachine(this, this);
    //二级状态
    CombatStateMachine = new FCombatStateMachine(this, this);
    //三级状态
    ActionStateMachine = new FActionsStateMachine(this, this);
    //四级状态
    MovingStateMachine = new FMovingStateMachine(this, this);
}


ABaseCharacter::~ABaseCharacter()
{
    delete RotationModule;
    RotationModule = nullptr;
    delete MovingModule;
    MovingModule = nullptr;

    /*状态机-销毁*/
    delete TopStateMachine;
    TopStateMachine = nullptr;
    delete CombatStateMachine;
    CombatStateMachine = nullptr;
    delete ActionStateMachine;
    ActionStateMachine = nullptr;
    delete MovingStateMachine;
    MovingStateMachine = nullptr;
}


void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 从骨骼网格组件获取动画实例
    BaseAnimation = Cast<UFBaseAnimation>(GetMesh()->GetAnimInstance());

    RotationModule->InitRotationModel(AngleRangeRotationSpeeds); //旋转模块初始化
    // 设置起始移动状态为行走
    SetMoveState(EMoveState::Walking);

    /*状态机-启动*/
    TopStateMachine->Transition(new FTopState(this, this, ETopState::Living));
    CombatStateMachine->Transition(new FCombatState(this, this, ECombatState::Idle));
    ActionStateMachine->Transition(new FActionsState(this, this, ECharacterBehavior::Idle));
    MovingStateMachine->Transition(new FMovingState(this, this, EMoveState::Walking));
}


void ABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 状态机更新
    TopStateMachine->Update(DeltaTime);
    CombatStateMachine->Update(DeltaTime);
    ActionStateMachine->Update(DeltaTime);
    MovingStateMachine->Update(DeltaTime);
    // 移动模块更新（现在只更新了 移动方向，移动的具体操作由AIMove执行）
    MovingModule->MovingModuleTick(DeltaTime);

    //转向模块更新
    RotationModule->RotationModuleTick();
}

/*SetupPlayerInputComponent 是 UE 的 APawn 基类提供的虚函数，专门用于绑定玩家输入。
调用时机： 当玩家控制器（PlayerController）接管该 Pawn 时，引擎自动调用一次。 */
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


/*蓝图调用 移动相关 Start */
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
        CurrentRotaType = EActorRotaType::Rotating;
        break;
    default: ;
    }
}

void ABaseCharacter::SetMoveState(EMoveState InMoveState)
{
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

void ABaseCharacter::OnMoveEnd()
{
    // 重置行为状态为闲置
    SetBehavior(ECharacterBehavior::Idle);
}

/*蓝图调用 移动相关 End */


/*蓝图调用 转向相关 start */
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

/*蓝图调用 转向相关 end */


/*蓝图调用 角色状态相关 Start*/
void ABaseCharacter::SetCharacterState(ECombatState InCharacterState)
{
    if (CurrentCharacterState == InCharacterState) return;
    CurrentCharacterState = InCharacterState;
    OnCharacterStateChanged.Broadcast(CurrentCharacterState);
}

/*蓝图调用 角色状态相关 End*/


/*蓝图调用 战斗相关 Start*/
void ABaseCharacter::ActivateCombat(ECombatType InCombatType)
{
    SetBehavior(ECharacterBehavior::Attack);
    CurrentCombatType = InCombatType;
    OnCombatTypeChanged.Broadcast(CurrentCombatType);
}

/*蓝图调用 战斗相关 End*/


/*委托 行为切换  Start*/
void ABaseCharacter::SetBehavior(ECharacterBehavior NewBehavior)
{
    // if (CurrentBehavior != NewBehavior)
    //     CurrentBehavior = NewBehavior;
    // OnBehaviorChanged.Broadcast(CurrentBehavior, CurrentMoveState);
}

/*委托 行为切换  End*/


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

void ABaseCharacter::SetCurrentMoveSpeed_Implementation(const EMoveState NewMoveState)
{
    switch (NewMoveState)
    {
    case EMoveState::Walking:
        GetCharacterMovement()->MaxWalkSpeed = CharacterData.WalkSpeed;
        break;
    case EMoveState::Running:
        GetCharacterMovement()->MaxWalkSpeed = CharacterData.RunSpeed;
        break;
    }
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

ECharacterBehavior ABaseCharacter::GetBehaviorState_Implementation() const
{
    // 返回当前角色的行为状态
    return CurrentBehavior;
}

void ABaseCharacter::SetBehaviorState_Implementation(const ECharacterBehavior NewBehavior)
{
    CurrentBehavior = NewBehavior;
}


void ABaseCharacter::SetTargetRotationDirection_Implementation(const FVector& NewDirection)
{
    // 设置当前角色的目标旋转方向
    TargetRotationDirection = NewDirection;
}

float ABaseCharacter::GetHealth_Implementation() const
{
    // 返回当前角色的生命值
    return CharacterData.Health;
}

void ABaseCharacter::SetHealth_Implementation(float NewHealth)
{
    if (CharacterData.Health == NewHealth)
        return;
    // 设置生命值并广播变化
    CharacterData.Health = NewHealth;
    OnHealthChanged.Broadcast(CharacterData.Health);
    UE_LOG(LogTemp, Log, TEXT("触发血量改变事件"));
}

/*接口实现 End*/


/*状态机 相关 Start*/
//切换定级状态机
void ABaseCharacter::SwitchTopState_Implementation(const ETopState InTopState)
{
    TopStateMachine->Transition(new FTopState(this, this, InTopState));
}
//切换战斗状态机
void ABaseCharacter::SwitchCombatState_Implementation(const ECombatState InCharacterState)
{
    CombatStateMachine->Transition(new FCombatState(this, this, InCharacterState));
}
//切换战斗动画
void ABaseCharacter::SwitchCombatAnimation_Implementation(const float Value)
{
    BaseAnimation->SetIdleToCombat(Value);
}

//切换行为状态机
void ABaseCharacter::SwitchBehaviourState_Implementation(const ECharacterBehavior NewBehavior)
{
    ActionStateMachine->Transition(new FActionsState(this, this, NewBehavior));
}

//切换行为动画
void ABaseCharacter::SwitchBehaviourAnimation_Implementation(const ECharacterBehavior NewBehavior)
{
    BaseAnimation->SwitchBehaviourState(NewBehavior);
}
//切换移动状态机
void ABaseCharacter::SwitchMovingState_Implementation(const EMoveState NewMoveState)
{
   // UE_LOG(LogTemp, Log, TEXT("SwitchMovingState_Implementation"));
    MovingStateMachine->Transition(new FMovingState(this, this, NewMoveState));
}
//切换移动动画
void ABaseCharacter::SwitchMoveAnimation_Implementation(const EMoveState NewMoveState)
{
    if (BaseAnimation)
    {
        //UE_LOG(LogTemp, Log, TEXT("Enable Change MoveState"));
        BaseAnimation->SwitchMoveState(NewMoveState);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("BaseAnimation is not valid!"));
    }
}

/*状态机 相关 End*/