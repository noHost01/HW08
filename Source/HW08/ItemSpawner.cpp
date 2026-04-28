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

	int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
	AItemSpawnPoint* SelectedPoint = SpawnPoints[RandomIndex];

	if (SelectedPoint)
	{
		ACollectItemActor* SpawnedItem = GetWorld()->SpawnActor<ACollectItemActor>(
			ItemClass,
			SelectedPoint->GetActorLocation(),
			SelectedPoint->GetActorRotation()
		);

		if (SpawnedItem)
		{
			SpawnedItem->SetOwnerSpawner(this);
		}

		UE_LOG(LogTemp, Warning, TEXT("Item Spawned at Point Index: %d"), RandomIndex);
	}
}

