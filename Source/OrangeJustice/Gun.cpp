// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "ShooterCharacter.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  GunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root Component"));
  SetRootComponent(GunRootComponent);

  GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
  GunMesh->SetupAttachment(GunRootComponent);
}

void AGun::PullTrigger()
{
  UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));

  APawn* OwnerPawn = Cast<APawn>(GetOwner());
  if (!OwnerPawn) return;
  AController *OwnerController = OwnerPawn->GetController();
  if (!OwnerController) return;

  FVector CameraLocation;
  FRotator CameraRotation;
  OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

  // DrawDebugCamera(GetWorld(), CameraLocation, CameraRotation, 90.f, 1.f, FColor::Red, true);

  FVector End = CameraLocation + CameraRotation.Vector() * MaxRange;
  // TODO: LineTrace

  FHitResult HitResult;
  bool LineTraceBlocked = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_GameTraceChannel1);
  if (LineTraceBlocked)
  {
    FVector ShotDirection = -CameraRotation.Vector();
    UGameplayStatics::SpawnEmitterAtLocation(
      this, 
      BulletImpactParticles, 
      HitResult.ImpactPoint, 
      ShotDirection.Rotation()
    );
    if (AShooterCharacter *HitCharacter = Cast<AShooterCharacter>(HitResult.GetActor()))
    {
      FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
      HitCharacter->TakeDamage(Damage, DamageEvent, OwnerController, this);
    }
  }
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

