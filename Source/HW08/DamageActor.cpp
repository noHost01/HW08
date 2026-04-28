// DamageActor.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivalPlayer.h"

ADamageActor::ADamageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamageActor::OnDamageOverlap);
}

void ADamageActor::OnDamageOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ASurvivalPlayer* Player = Cast<ASurvivalPlayer>(OtherActor);

	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageActor Hit! Damage: %d"), DamageAmount);

		Player->TakeDamageFromActor(DamageAmount);
	}
}

