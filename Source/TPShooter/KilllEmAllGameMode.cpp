// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::Pawnkilled(APawn *PawnKilled)
{
    Super::Pawnkilled(PawnKilled);
    // UE_LOG(LogTemp, Warning, TEXT("A pawn was killed!"));

    // to check if the pawn is of type player controller
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        // replaced by end game
        // PlayerController->GameHasEnded(nullptr, false);
        EndGame(false);
    }

    // calculate win condition
    for (AShooterAIController *Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

// determines if player or AI is won
void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        // we can use this method to determine if palyer won or ai
        // bool bIsPlayerController = Controller->IsPlayerController();
        // if (bIsPlayerWinner)
        // {
        //     Controller->GameHasEnded(nullptr, bIsPlayerController);
        // }
        // else
        // {
        //     Controller->GameHasEnded(nullptr, !bIsPlayerController);
        // }
        // or we can do above statements simpler
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        // nullptr puts the focus away is from pawn if player Wins
        // but we want to focus on player pawn in case of winning
        // so we replace it with Controller->GmeHasEnded(Controller->GetPawn(),bIsWinner)
        // in most match games camera follows the killer but in this game we always follow the player
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
