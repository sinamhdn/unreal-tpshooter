// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "TPShooterGameModeBase.h"
#include "Weapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// by default it will spawn this c++ class
	// but we want to spawn blueprint rifle child of this c++ class
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);

	// hide the weapon already available on character
	// look at definition to see how to use this function
	GetMesh()->HideBoneByName(TEXT("weapon_l"), EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// attach gun to the owner
	// for FAttachmentTransformRules we can define our own or use these predefined rules
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r_socket"));
	// essential to set the owner useful in some scenarios
	Weapon->SetOwner(this);

	Health = MaxHealth;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("LookUB"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRL"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUBCTRL"), this, &APlayerCharacter::LookUBCTRL);
	PlayerInputComponent->BindAxis(TEXT("LookRLCTRL"), this, &APlayerCharacter::LookRLCTRL);
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &APlayerCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveRL"), this, &APlayerCharacter::MoveRL);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// do this because DamageToApply may be bigger than Health //
	DamageToApply = FMath::Min(Health, DamageToApply);
	/////////////////////////////////////////////////////////////
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		// inform game mode that the character is dead
		ATPShooterGameModeBase *GameMode = GetWorld()->GetAuthGameMode<ATPShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->Pawnkilled(this);
		}

		// make dead character not controllable by both AI and controller (if you detch before notifying the pawn will not have a controller)
		DetachFromControllerPendingDestroy();
		// disable collision if character is dead
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool APlayerCharacter::IsDead() const
{
	return Health <= 0;
}

// contradicts with DRY principal as this functions just pass value to another function
// void APlayerCharacter::LookUB(float AxisValue)
//{
//	AddControllerPitchInput(AxisValue);
//}
//
// void APlayerCharacter::LookRL(float AxisValue)
//{
//	AddControllerYawInput(AxisValue);
//}

void APlayerCharacter::LookUBCTRL(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRLCTRL(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveFB(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRL(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

float APlayerCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void APlayerCharacter::Shoot()
{
	Weapon->PullTrigger();
}
