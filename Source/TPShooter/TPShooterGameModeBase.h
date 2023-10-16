// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPShooterGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class TPSHOOTER_API ATPShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void Pawnkilled(APawn *PawnKilled);
};
