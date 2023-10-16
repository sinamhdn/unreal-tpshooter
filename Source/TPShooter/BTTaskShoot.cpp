// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskShoot.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTaskShoot::UBTTaskShoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    APlayerCharacter *Character = Cast<APlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    APlayerCharacter *Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
    if(Player == nullptr){
        return EBTNodeResult::Failed;
    }
    if (!Player->IsDead())
    {
        Character->Shoot();
    }
    return EBTNodeResult::Succeeded;
}
