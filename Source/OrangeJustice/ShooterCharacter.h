// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class ORANGEJUSTICE_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

  UFUNCTION(BlueprintPure)
  bool GetIsAlive() const { return bAlive; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
    float DamageAmount, 
    struct FDamageEvent const& DamageEvent, 
    class AController* EventInstigator, 
    AActor* DamageCauser
  ) override;


private:
  void MoveForward(float AxisValue);
  void MoveRight(float AxisValue);
  void LookUpRate(float AxisValue);
  void LookRightRate(float AxisValue);

  void Shoot();

  UPROPERTY(EditAnywhere)
  float RotationRate = 50;

  UPROPERTY(EditDefaultsOnly, Category = "Combat")
  float MaxHealth = 100.f;

  UPROPERTY(VisibleAnywhere, Category = "Combat")
  float Health;

  UPROPERTY(VisibleAnywhere, Category = "Combat")
  bool bAlive = true;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<AGun> GunClass;

  UPROPERTY()
  AGun* Gun;
};
