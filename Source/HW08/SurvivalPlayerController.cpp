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