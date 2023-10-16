// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TPSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	// call this when you pull the trigger on the gun
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *WeaponRoot;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *WeaponSkeletalMesh;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *WeaponAimSkeletalMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *WeaponStaticMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *WeaponAimStaticMesh;

	// editanywhere so that you can change particle effect in run time
	UPROPERTY(EditAnyWhere)
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnyWhere)
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnyWhere)
	UParticleSystem *ImpactEffect;

	UPROPERTY(EditAnyWhere)
	USoundBase *ImpactSound;

	// max range that the bullet hits
	UPROPERTY(EditAnyWhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnyWhere)
	float Damage = 10;

	bool WeaponTrace(FHitResult &Hit, FVector &ShotDirection);

	AController *GetOwnerController() const;
};
