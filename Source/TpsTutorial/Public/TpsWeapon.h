// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TpsTutorial.h"
#include "TpsWeapon.generated.h"

UCLASS()
class TPSTUTORIAL_API ATpsWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATpsWeapon();

protected:
	// =============== Functions =====================

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// =============== Variables =====================

	// The mesh component of this weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

	// The Muzzle effect of this weapon when firing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* MuzzleEffect;
	
	// The line tracing effect when firing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TracerEffect;

	// The default impact effect when it hits a target
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* DefaultImpactEffect;

	// The impact effect when it hits flesh (e.g., humans)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* FleshImpactEffect;

	// The damage type of this weapon
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Effects")
	TSubclassOf<class UDamageType> DamageType;

	// Is this an automatic weapon. Default is false.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Key Properties")
	bool Auto = true;

	// Base damage of this weapon. Default is 20
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Key Properties")
	float BaseDamage = 20.f;

	// The number of fires per second. Default is 10
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Key Properties")
	float FireRatePerSecond = 10.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The fire function of this weapon
	UFUNCTION(BlueprintCallable)
	virtual void Fire(const bool& IsHit, const FHitResult& HitRes, const FVector& TracingEndLocation);

	// Return if this weapon is automatic or not
	bool IsAutomatic() const;

	// Return the rate of fire per second for this weapon
	float GetFireRatePerSecond() const;
};
