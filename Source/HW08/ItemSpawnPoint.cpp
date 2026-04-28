// ItemSpawnPoint.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawnPoint.h"
#include "Components/BillboardComponent.h"

AItemSpawnPoint::AItemSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
}

