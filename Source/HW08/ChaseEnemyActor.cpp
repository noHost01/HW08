// ChaseEnemyActor.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemyActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalPlayer.h"

AChaseEnemyActor::AChaseEnemyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	DamageCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollision"));
	DamageCollision->SetupAttachment(RootComponent);
	DamageCollision->InitSphereRadius(100.0f);
	DamageCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AChaseEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemyActor::OnEnemyOverlap);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AChaseEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerActor)
	{
		FVector Direction = PlayerActor->GetActorLocation() - GetActorLocation();
		Direction.Z = 0.0f;

		if (!Direction.IsNearlyZero())
		{
			FRotator LookRotation = Direction.Rotation();
			SetActorRotation(LookRotation);

			AddMovementInput(Direction.GetSafeNormal(), 1.0f);
		}
	}
}

void AChaseEnemyActor::OnEnemyOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ASurvivalPlayer* Player = Cast<ASurvivalPlayer>(OtherActor);

	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Hit Player! Damage: %d"), DamageAmount);

		Player->TakeDamageFromActor(DamageAmount);

		SetActorLocation(StartLocation);
	}
}

void AChaseEnemyActor::UpdateActiveByWave(int32 CurrentWave)
{
	bool bShouldActive = CurrentWave >= ActiveWave;
	SetEnemyActive(bShouldActive);

	SetActorHiddenInGame(!bShouldActive);
	SetActorEnableCollision(bShouldActive);
	SetActorTickEnabled(bShouldActive);

	if (bShouldActive)
	{
		SetActorLocation(StartLocation);
	}
}

void AChaseEnemyActor::SetEnemyActive(bool bActive)
{
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
	SetActorTickEnabled(bActive);

	if (bActive)
	{
		SetActorLocation(StartLocation);
	}
}

