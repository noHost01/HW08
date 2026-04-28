// CollectItemActor.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectItemActor.h"
#include "SurvivalGameState.h"
#include "ItemSpawner.h"
#include "TimerManager.h"
#include "SurvivalGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivalPlayer.h"

ACollectItemActor::ACollectItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->InitSphereRadius(50.0f);
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OwnerSpawner = nullptr;
}

void ACollectItemActor::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACollectItemActor::OnItemOverlap);
}

void ACollectItemActor::OnItemOverlap(
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
		UE_LOG(LogTemp, Warning, TEXT("Collect Item! ScoreValue: %d"), ScoreValue);

		ASurvivalGameState* GameState = GetWorld()->GetGameState<ASurvivalGameState>();

		if (GameState)
		{
			GameState->AddCollectedCount();
		}

		AItemSpawner* SavedSpawner = OwnerSpawner;

		Destroy();

		if (SavedSpawner)
		{
			FTimerHandle SpawnTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				SpawnTimerHandle,
				[SavedSpawner]()
				{
					if (IsValid(SavedSpawner))
					{
						SavedSpawner->SpawnItem();
					}
				},
				0.1f,
				false
			);
		}
	}

}

int32 ACollectItemActor::GetScoreValue() const
{
	return ScoreValue;
}

void ACollectItemActor::SetOwnerSpawner(AItemSpawner* Spawner)
{
	OwnerSpawner = Spawner;
}

