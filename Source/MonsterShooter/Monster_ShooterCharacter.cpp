// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_ShooterCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

#include "MonsterShooter_GameMode.h"

// Sets default values
AMonster_ShooterCharacter::AMonster_ShooterCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 95.f);

	TurnRate = 45.f;
	LookUpRate = 45.f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-39.65f, 1.75f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->CastShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.f, 0.f, 10.f);

}

// Called when the game starts or when spawned
void AMonster_ShooterCharacter::BeginPlay() {
	Super::BeginPlay();

	GunMesh->AttachToComponent(HandsMesh, 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		TEXT("GripPoint"));

	World = GetWorld();

	AnimInstance = HandsMesh->GetAnimInstance();


}

// Called every frame
void AMonster_ShooterCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster_ShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMonster_ShooterCharacter::OnFire);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMonster_ShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMonster_ShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMonster_ShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMonster_ShooterCharacter::LookAtRate);

}

void AMonster_ShooterCharacter::OnFire() {
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = ((MuzzleLocation != nullptr) ?
			MuzzleLocation->GetComponentLocation() :
			GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AProjectile>(Projectile,
			SpawnLocation, SpawnRotation, ActorSpawnParams);

		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		}
		if (FireAnimation != NULL && AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.0f);
		}


	}
}

void AMonster_ShooterCharacter::MoveForward(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMonster_ShooterCharacter::MoveRight(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMonster_ShooterCharacter::TurnAtRate(float Rate) {
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMonster_ShooterCharacter::LookAtRate(float Rate) {
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMonster_ShooterCharacter::DealDamage(float DamageAmount) {
	Health -= DamageAmount;

	if (Health <= 0.f) {
		// restart game
		AMonsterShooter_GameMode* MyGameMode = Cast<AMonsterShooter_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (MyGameMode) {
			MyGameMode->RestartGameplay(false);
		}
	}

	//Destroy();
}
