// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // focus on the player
    // SetFocus(PlayerPawn);

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        // moved to Tick
        // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        // // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // replaced by behvior tree
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    //
    // // move and focus if in line of sight and stop in not in line of sight
    // if (LineOfSightTo(PlayerPawn))
    // {
    //     // put set focus in tick so the character turns toward the player
    //     SetFocus(PlayerPawn);
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    // }
    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }

    // moved to services
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // if (LineOfSightTo(PlayerPawn))
    // {
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    // }
    // else
    // {
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    // }
}

bool AShooterAIController::IsDead() const
{
    APlayerCharacter *ControlledCharacter = Cast<APlayerCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}
