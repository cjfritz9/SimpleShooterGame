// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class ORANGEJUSTICE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

  void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

  UPROPERTY(VisibleAnywhere)
  USceneComponent *GunRootComponent;

  UPROPERTY(VisibleAnywhere)
  USkeletalMeshComponent *GunMesh;

  UPROPERTY(EditAnywhere, Category = "Particle Effects")
  UParticleSystem *MuzzleFlash;

  UPROPERTY(EditAnywhere, Category = "Particle Effects")
  UParticleSystem *BulletImpactParticles;

  UPROPERTY(EditAnywhere, Category = "Gunplay")
  float MaxRange = 10000.f;

  UPROPERTY(EditAnywhere)
  float Damage = 10.f;
};
