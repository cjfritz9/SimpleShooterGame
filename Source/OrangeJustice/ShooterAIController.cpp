// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
  Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
  float DistanceToPlayer = FVector::Dist(PlayerPawn->GetActorLocation(), GetPawn()->GetActorLocation());
  if (PlayerPawn && DistanceToPlayer < 1200.f)
  {
    SetFocus(PlayerPawn);
    MoveToActor(PlayerPawn, 800.f);
  }
}
