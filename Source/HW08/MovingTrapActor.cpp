// MovingTrapActor.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTrapActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivalPlayer.h"

AMovingTrapActor::AMovingTrapActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetBoxExtent(FVector(100.0f, 30.0f, 100.0f));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMovingTrapActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMovingTrapActor::OnTrapOverlap);
	}
}

void AMovingTrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveDistance <= 0.0f || MoveSpeed <= 0.0f)
	{
		return;
	}

	FVector CurrentLocation = GetActorLocation();

	if (bMoveOnX)
	{
		CurrentLocation.X += MoveDirection * MoveSpeed * DeltaTime;

		if (FMath::Abs(CurrentLocation.X - StartLocation.X) >= MoveDistance)
		{
			MoveDirection *= -1;
		}
	}
	else
	{
		CurrentLocation.Y += MoveDirection * MoveSpeed * DeltaTime;

		if (FMath::Abs(CurrentLocation.Y - StartLocation.Y) >= MoveDistance)
		{
			MoveDirection *= -1;
		}
	}

	SetActorLocation(CurrentLocation);
}

void AMovingTrapActor::OnTrapOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	ASurvivalPlayer* Player = Cast<ASurvivalPlayer>(OtherActor);

	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving Trap Hit! Damage: %d"), DamageAmount);
		Player->TakeDamageFromActor(DamageAmount);
	}
}
