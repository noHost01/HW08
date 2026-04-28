// ItemSpawnPoint.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnPoint.generated.h"

class UBillboardComponent;

UCLASS()
class HW08_API AItemSpawnPoint : public AActor
{
	GENERATED_BODY()

	public:
		AItemSpawnPoint();

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
		UBillboardComponent* Billboard;
};