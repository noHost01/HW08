// SurvivalPlayerController.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

UCLASS()
class HW08_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowGameOverUI();

	protected:
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> HUDWidgetClass;

		UPROPERTY()
		UUserWidget* HUDWidget;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

		UPROPERTY()
		UUserWidget* GameOverWidget;
};

