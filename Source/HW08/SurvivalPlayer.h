// SurvivalPlayer.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class HW08_API ASurvivalPlayer : public ACharacter
{
	GENERATED_BODY()

	public:
		ASurvivalPlayer();

	protected:
		virtual void BeginPlay() override;
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* Camera;

		// 카메라 회전율
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float YawSensitivity = 0.7f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float PitchSensitivity = 0.5f;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* DefaultMappingContext;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LookAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpAction;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		int32 MaxHP = 100;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		int32 CurrentHP;

		void Move(const FInputActionValue& Value);
		void Look(const FInputActionValue& Value);
		void StartJump(const FInputActionValue& Value);
		void StopJump(const FInputActionValue& Value);

	public:
		UFUNCTION(BlueprintCallable, Category = "Status")
		void TakeDamageFromActor(int32 DamageAmount);

		UFUNCTION(BlueprintCallable, Category = "Status")
		int32 GetCurrentHP() const;
};
