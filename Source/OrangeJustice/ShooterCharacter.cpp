// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

  Gun = GetWorld()->SpawnActor<AGun>(GunClass);
  GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
  Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocketR"));
  Gun->SetOwner(this);

  Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

  // UNIVERSAL AXIS INPUTS
  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
  PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

  // MOUSE AXIS INPUTS
  PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
  PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

  // CONTROLLER AXIS INPUTS
  PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
  PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

  // ACTION INPUTS
  PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
  PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

}

float AShooterCharacter::TakeDamage(
  float DamageAmount, 
  struct FDamageEvent const& DamageEvent, 
  class AController* EventInstigator, 
  AActor* DamageCauser
)
{
  float DamageToApply = Super::TakeDamage(
    DamageAmount, 
    DamageEvent, 
    EventInstigator, 
    DamageCauser
  );
  if (Health > 0)
  {
    Health -= DamageToApply;
    if (Health <= 0)
    {
      bAlive = false;
    }
  }
  UE_LOG(LogTemp, Display, TEXT("Health Remaining: %f"), Health);
  return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
  AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
  AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
  AddControllerPitchInput(AxisValue *
    RotationRate * 
    GetWorld()->GetDeltaSeconds()
  );
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
  AddControllerYawInput(AxisValue *
    RotationRate * 
    GetWorld()->GetDeltaSeconds()
  );
}

void AShooterCharacter::Shoot()
{
  if (Gun)
  {
    Gun->PullTrigger();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Select A Gun Class In Character BP"));
  }
}
