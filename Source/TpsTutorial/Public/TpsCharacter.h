// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsWeapon.h"
#include "TpsCharacter.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;
class UTpsHealthComponent;
class UDamageType;
class AController;
class UInputComponent;
class UAnimMontage;

UENUM()
enum EWeaponID
{
	None = -1, LeftWeapon, RightWeapon
};

UCLASS()
class TPSTUTORIAL_API ATpsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsCharacter();

protected:
	// ============== FUNCTIONS ==============

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Shoot weapon function; will be looping if the current weapon is automatic
	void Fire();

	// dynamic delegate function on health changed
	UFUNCTION()
	void HandleHealthUpdate(UTpsHealthComponent* OwningHealthComp, float CurrentHealth, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Create the crosshair widget in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "BlueprintEvents")
	void CreateCrosshairWidgetEvent();

	// The event when starting zooming in camera. To be implemented in BP.
	UFUNCTION(BlueprintImplementableEvent, Category = "BlueprintEvents")
	void ZoomInCamera();

	// The event when starting zooming out camera. To be implemented in BP.
	UFUNCTION(BlueprintImplementableEvent, Category = "BlueprintEvents")
	void ZoomOutCamera();

	// The event to be fired when the anim montage of swapping weapon notifies
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void OnNotifySwapWeapon();

	// Bind axis and action inputs
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void StartShoot();
	void EndShoot();
	void ZoomIn();
	void ZoomOut();
	void StartRun();
	void EndRun();
	void SwapWeapon();

	// Helper function: Do single line trace by channel, determine end location, and fire weapon
	void LineTraceFromCameraByChannel(FHitResult& HitResult, ECollisionChannel TraceChannel);

	// Helper function: Spawn the weapon at the right socket
	void SpawnWeapon();

	// ================ VARIABLES ================
	// Main camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	// Spring Arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	// Health component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTpsHealthComponent* HealthComp;

	// The weapon class to spawn on the left back of character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ATpsWeapon> LeftWeaponClass;

	// The weapon class to spawn on the right back of character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ATpsWeapon> RightWeaponClass;

	// The spawned 2 weapon instances and the currently equipped weapon
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<ATpsWeapon*> EquippedWeapons;
	EWeaponID CurrentWeaponID;

	// The animation montage to play when swapping weapons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UAnimMontage* WeaponSwapMontage;

	// TThe weapon firing animation montage 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UAnimMontage* FireWeaponMontage;

	// Whether the player is zooming in
	UPROPERTY(BlueprintReadOnly, Category = "Camera Zoom")
	bool bAiming;

	// Set the scale of speed of looking around when aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float AimLookScale;

	// The FOV after zoom in
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float ZoomInArmLength;

	// The default FOV
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float DefaultArmLength;

	// The local rotation of this character when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float AimRotation;

	// Whether the character is dead or not
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bDead;

	// Whether the player is zooming in
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bRunning;

	// The actor to interact
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	AActor* InteractActor;

	// The timer handler for shooting weapon
	FTimerHandle TimerHandle;

	// The last fire time
	float LastFireTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
