// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AWeapon;
UCLASS()
class TPSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// for the character to recieve damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// to update heathbar based on health
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Shoot();

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 15;

	// EditDefaultsOnly to hint people it wont be updated on run time and just spawns
	// TSubclassOf<AWeapon> to restrict blueprint from selecting ny class that is not sub class of AWeapon
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY()
	AWeapon *Weapon;
	UPROPERTY(EditDefaultsOnly)

	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float Health;

	// void LookUB(float AxisValue);
	// void LookRL(float AxisValue);
	void LookUBCTRL(float AxisValue);
	void LookRLCTRL(float AxisValue);
	void MoveFB(float AxisValue);
	void MoveRL(float AxisValue);
};
