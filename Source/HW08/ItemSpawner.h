// ItemSpawner.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class AItemSpawnPoint;
class ACollectItemActor;

UCLASS()
class HW08_API AItemSpawner : public AActor
{
	GENERATED_BODY()

	public:
		AItemSpawner();

		void SpawnItem();

	protected:
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TSubclassOf<ACollectItemActor> ItemClass;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
		TArray<AItemSpawnPoint*> SpawnPoints;

		void FindSpawnPoints();
};
