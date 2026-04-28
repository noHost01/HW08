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

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemyActor::OnEnemyOverlap);
}

void AChaseEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerActor)
	{
		FVector Direction = (PlayerActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction, 1.0f);
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

