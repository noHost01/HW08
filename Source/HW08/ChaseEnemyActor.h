// ChaseEnemyActor.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseEnemyActor.generated.h"

class USphereComponent;

UCLASS()
class HW08_API AChaseEnemyActor : public ACharacter
{
	GENERATED_BODY()

	public:
		AChaseEnemyActor();

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float MoveSpeed = 250.0f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int32 DamageAmount = 10;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
		FVector StartLocation;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
		USphereComponent* DamageCollision;

		UFUNCTION()
		void OnEnemyOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int32 ActiveWave = 1;

	public:
		void UpdateActiveByWave(int32 CurrentWave);
		void SetEnemyActive(bool bActive);
};
