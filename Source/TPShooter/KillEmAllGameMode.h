// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 *
 */
UCLASS()
class TPSHOOTER_API AKillEmAllGameMode : public ATPShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void Pawnkilled(APawn *PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
