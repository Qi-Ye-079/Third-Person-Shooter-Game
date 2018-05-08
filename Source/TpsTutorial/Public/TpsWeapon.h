// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TpsWeapon.generated.h"

UCLASS()
class TPSTUTORIAL_API ATpsWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATpsWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UDamageType> DamageType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ShootProjectile(class UCameraComponent* CameraComp);
	
	
};