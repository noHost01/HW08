// CollectItemActor.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectItemActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class AItemSpawner;

UCLASS()
class HW08_API ACollectItemActor : public AActor
{
	GENERATED_BODY()

	public:
		ACollectItemActor();

	protected:
		virtual void BeginPlay() override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		USphereComponent* Collision;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		UStaticMeshComponent* Mesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ScoreValue = 1;

		UFUNCTION()
		void OnItemOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	public:
		int32 GetScoreValue() const;
		void SetOwnerSpawner(AItemSpawner* Spawner);

	private:
		UPROPERTY()
		AItemSpawner* OwnerSpawner;
};
