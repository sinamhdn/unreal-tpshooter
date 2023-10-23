// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));
	SetRootComponent(WeaponRoot);

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(WeaponRoot);

	WeaponAimSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponAimSkeletalMesh"));
	WeaponAimSkeletalMesh->SetupAttachment(WeaponSkeletalMesh);

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	WeaponStaticMesh->SetupAttachment(WeaponRoot);

	WeaponAimStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponAimStaticMesh"));
	WeaponAimStaticMesh->SetupAttachment(WeaponStaticMesh);
}

void AWeapon::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponSkeletalMesh, TEXT("muzzle_flash_socket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponSkeletalMesh, TEXT("muzzle_flash_socket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = WeaponTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		// draw guide points at hit location
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Green, true);

		// add particle effect to where the bullet hits
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		// sending the damage to the target
		AActor *HitActor = Hit.GetActor();
		
		if (HitActor != nullptr)
		{
			// if (GetOwner() == nullptr) { return; }
			// if (*(GetOwner()->Tags.GetData()) == *(HitActor->Tags.GetData())) return;
			// UE_LOG(LogTemp, Warning, TEXT("The Actor's tags are %s and %s"), *(this->GetOwner()->Tags.GetData()->ToString()), *(HitActor->Tags.GetData()->ToString()));
			// FString TestCondition = (*(GetOwner()->Tags.GetData()->ToString()) == *(HitActor->Tags.GetData()->ToString())) ? "true" : "false";
			// UE_LOG(LogTemp, Warning, TEXT("The Actor's tag is %s."), *(GetOwner()->Tags.GetData()->ToString()));
			
			// if we have some kind of damage type like fire or poison damage we call replace nullptr
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			// to avoid nullptr error
			if (OwnerController == nullptr) return;

			/*
			if (GetOwner()->Tags.GetData()->ToString() == FString(ANSI_TO_TCHAR("Enemy")))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hello"));
				if (HitActor->Tags.GetData()->ToString() == FString(ANSI_TO_TCHAR("Enemy")))
				{
					UE_LOG(LogTemp, Warning, TEXT("Helloooooooo"));
					return;
				}
			}
			*/

			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeapon::WeaponTrace(FHitResult &Hit, FVector &ShotDirection)
{
	AController *OwnerController = GetOwnerController();
	// to avoid nullptr error
	if (OwnerController == nullptr)
		return false;
	FVector Location;
	FRotator Rotation;
	// returns the Location and Rotaion of characters viewpoint to these variables
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// to find where the shot is comming from
	ShotDirection = -Rotation.Vector();

	// draw raytracing guides from the weapon to the target
	// DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 90, 2, FColor::Blue, true);
	// draw raytracing guides from the camera to the target
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	// get the end of the line trace by adding character location to the vector that points at character angle
	FVector End = Location + Rotation.Vector() * MaxRange;
	// to prevent killing himself (ignore gun and the shooter)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// DOESNT WORK BECAUSE WE DON'T HAVE HITRESULT YET WE GET IT AFTER LINETRACE DONE
	/*
	AActor* HitActor = Hit.GetActor();
	if (HitActor != nullptr)
	{
		if (GetOwner()->Tags.GetData()->ToString() == FString(ANSI_TO_TCHAR("Enemy")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello"));
			if (HitActor->Tags.GetData()->ToString() == FString(ANSI_TO_TCHAR("Enemy")))
			{
				UE_LOG(LogTemp, Warning, TEXT("Helloooooooo"));
				Params.AddIgnoredActor(Hit.GetActor());
			}
		}
	}
	*/

	// line trace the gun point
	// Params are optional in this case we needed to pass them
	// We added this line to stop enemies from killing eachother ECC_GameTraceChannel2 will be ignored by the enemy bp collision settings
	if (GetOwner()->Tags.GetData()->ToString() == FString(ANSI_TO_TCHAR("Enemy")))
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
		return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
	}
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController *AWeapon::GetOwnerController() const
{
	// get the owner of the gun which we defind in PlayerCharacter class to be that class
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	// to avoid nullptr error
	if (OwnerPawn == nullptr)
		return nullptr;
	// get controller from the owner
	return OwnerPawn->GetController();
}
