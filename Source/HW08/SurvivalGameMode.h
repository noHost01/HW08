// SurvivalGameMode.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameMode.generated.h"

UCLASS()
class HW08_API ASurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver();
};
