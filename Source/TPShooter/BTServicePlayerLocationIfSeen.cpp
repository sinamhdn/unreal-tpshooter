// Fill out your copyright notice in the Description page of Project Settings.

#include "BTServicePlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTServicePlayerLocationIfSeen::UBTServicePlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTServicePlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        // change this to point to the PlayerPawn instead of its location
        // OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
