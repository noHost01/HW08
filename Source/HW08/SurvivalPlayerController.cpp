// SurvivalPlayerController.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();

			UE_LOG(LogTemp, Warning, TEXT("HUD Created"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass is not set!"));
	}
}

void ASurvivalPlayerController::ShowGameOverUI()
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UUserWidget>(this, GameOverWidgetClass);

		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport(100);

			bShowMouseCursor = true;

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);

			UE_LOG(LogTemp, Warning, TEXT("GameOver UI Created"));
		}
	}
}