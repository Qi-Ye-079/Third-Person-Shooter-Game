// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "Components/TpsHealthComponent.h"


// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create health component
	HealthComp = CreateDefaultSubobject<UTpsHealthComponent>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	// Subscribe to the health update event
	HealthComp->OnHealthChanged.AddDynamic(this, &AEnemyAI::HandleHealthUpdate);
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyAI::HandleHealthUpdate(UTpsHealthComponent* OwningHealthComp, float CurrentHealth, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// Log current health
	UE_LOG(LogTemp, Warning, TEXT("Current health: %f"), CurrentHealth);

	if (CurrentHealth <= 0.f)
	{
		Destroy();
	}
}
