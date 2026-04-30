// SurvivalGameState.cpp

// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGameState.h"
#include "ChaseEnemyActor.h"
#include "Kismet/GameplayStatics.h"

ASurvivalGameState::ASurvivalGameState()
{
	CurrentWave = 1;
	CollectedCount = 0;
	TargetCollectCount = 5;
}

void ASurvivalGameState::AddCollectedCount()
{
	if (bIsWaveTransitioning)
	{
		return;
	}

	CollectedCount++;

	UE_LOG(LogTemp, Warning, TEXT("Collected: %d / %d"), CollectedCount, TargetCollectCount);

	if (IsWaveClear())
	{
		bIsWaveTransitioning = true;

		UE_LOG(LogTemp, Warning, TEXT("Wave %d Clear! Next Wave in 5 seconds..."), CurrentWave);

		SetAllEnemiesActive(false);

		GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&ASurvivalGameState::BeginNextWave,
			5.0f,
			false
		);
	}
}

void ASurvivalGameState::StartNextWave()
{
	if (CurrentWave >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("===== LEVEL CLEAR ====="));
		return;
	}

	CurrentWave++;
	CollectedCount = 0;

	if (CurrentWave == 2)
	{
		TargetCollectCount = 10;
	}
	else if (CurrentWave == 3)
	{
		TargetCollectCount = 15;
	}

	bIsWaveTransitioning = false;

	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start! Target: %d"), CurrentWave, TargetCollectCount);

	UpdateEnemiesByWave();
}

bool ASurvivalGameState::IsWaveClear() const
{
	return CollectedCount >= TargetCollectCount;
}

void ASurvivalGameState::UpdateEnemiesByWave()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChaseEnemyActor::StaticClass(), Enemies);

	for (AActor* Actor : Enemies)
	{
		AChaseEnemyActor* Enemy = Cast<AChaseEnemyActor>(Actor);

		if (Enemy)
		{
			Enemy->UpdateActiveByWave(CurrentWave);
		}
	}
}

bool ASurvivalGameState::IsWaveTransitioning() const
{
	return bIsWaveTransitioning;
}

void ASurvivalGameState::BeginNextWave()
{
	StartNextWave();
}

void ASurvivalGameState::SetAllEnemiesActive(bool bActive)
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChaseEnemyActor::StaticClass(), Enemies);

	for (AActor* Actor : Enemies)
	{
		AChaseEnemyActor* Enemy = Cast<AChaseEnemyActor>(Actor);

		if (Enemy)
		{
			Enemy->SetEnemyActive(bActive);
		}
	}
}

void ASurvivalGameState::BeginPlay()
{
	Super::BeginPlay();

	UpdateEnemiesByWave();
}
