// MovingTrapActor.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTrapActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class HW08_API AMovingTrapActor : public AActor
{
	GENERATED_BODY()

public:
	AMovingTrapActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap")
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float MoveDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	int32 DamageAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	bool bMoveOnX = false;

	FVector StartLocation;

	int32 MoveDirection = 1;

	UFUNCTION()
	void OnTrapOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
