// SurvivalGameState.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SurvivalGameState.generated.h"

UCLASS()
class HW08_API ASurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASurvivalGameState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CollectedCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 TargetCollectCount;

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void AddCollectedCount();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartNextWave();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	bool IsWaveClear() const;
};
