// SurvivalGameState.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameState.h"

ASurvivalGameState::ASurvivalGameState()
{
	CurrentWave = 1;
	CollectedCount = 0;
	TargetCollectCount = 5;
}

void ASurvivalGameState::AddCollectedCount()
{
	CollectedCount++;

	UE_LOG(LogTemp, Warning, TEXT("Collected: %d / %d"), CollectedCount, TargetCollectCount);

	if (IsWaveClear())
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave %d Clear!"), CurrentWave);
		StartNextWave();
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

	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start! Target: %d"), CurrentWave, TargetCollectCount);
}

bool ASurvivalGameState::IsWaveClear() const
{
	return CollectedCount >= TargetCollectCount;
}