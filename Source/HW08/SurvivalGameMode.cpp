// SurvivalGameMode.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ASurvivalGameMode::ASurvivalGameMode()
{
}

void ASurvivalGameMode::GameOver()
{
	UE_LOG(LogTemp, Error, TEXT("===== GAME OVER ====="));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->SetPause(true);
	}
}