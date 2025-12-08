// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationData.h"
#include "NavigationSystem.h"


ABaseCharacter::ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    //ANavigationData*
    // 2. 创建路径查询请求
    FNavAgentProperties AgentProperties; // 可以设置Agent的属性，如半径、高度
    
    const INavAgentInterface* NavAgent = Cast<INavAgentInterface>(this);
    FNavAgentProperties AgentProps = NavAgent ? NavAgent->GetNavAgentPropertiesRef() : FNavAgentProperties();

    // 3. 获取导航数据 (NavMesh)
    const ANavigationData* NavData = NavSystem->GetNavDataForProps(AgentProps, GetActorLocation());

    FVector EndPos = FVector(0.f, 0.f, 0.f);

    FPathFindingQuery Query;
    Query.NavData = NavData;
    Query.StartLocation = GetActorLocation();
    Query.EndLocation = EndPos;


    // 3. 执行寻路查询
    FPathFindingResult Result = NavSystem->FindPathSync(Query);
   
    // 4. 获取路径点并找到“下一个”点
    // Result.Path->GetPathPoints() 返回一个 TArray<FNavPathPoint>
    const TArray<FNavPathPoint>& PathPoints = Result.Path->GetPathPoints();
    Result.Path->GetPathPoints();

    //NavSystem->GetPathName()
}


void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}


void ABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}