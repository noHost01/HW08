// ItemSpawner.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "ItemSpawnPoint.h"
#include "CollectItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	FindSpawnPoints();
	SpawnItem();
}

void AItemSpawner::FindSpawnPoints()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnPoint::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AItemSpawnPoint* SpawnPoint = Cast<AItemSpawnPoint>(Actor);
		if (SpawnPoint)
		{
			SpawnPoints.Add(SpawnPoint);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnPoint Count: %d"), SpawnPoints.Num());
}

void AItemSpawner::SpawnItem()
{
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemClass is not set!"));
		return;
	}

	if (SpawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No SpawnPoints found!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 TryCount = 0; TryCount < SpawnPoints.Num(); TryCount++)
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		AItemSpawnPoint* SelectedPoint = SpawnPoints[RandomIndex];

		if (!SelectedPoint)
		{
			continue;
		}

		FVector SpawnLocation = SelectedPoint->GetActorLocation();
		SpawnLocation.Z += 80.0f;

		FRotator SpawnRotation = SelectedPoint->GetActorRotation();

		ACollectItemActor* SpawnedItem = GetWorld()->SpawnActor<ACollectItemActor>(
			ItemClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		if (SpawnedItem)
		{
			SpawnedItem->SetOwnerSpawner(this);

			UE_LOG(LogTemp, Warning, TEXT("Item Spawned Success! Index: %d Location: %s"),
				RandomIndex,
				*SpawnLocation.ToString()
			);

			return;
		}

		UE_LOG(LogTemp, Error, TEXT("Item Spawn Failed! Retry... Index: %d Location: %s"),
			RandomIndex,
			*SpawnLocation.ToString()
		);
	}

	UE_LOG(LogTemp, Error, TEXT("All Spawn Attempts Failed!"));
}

