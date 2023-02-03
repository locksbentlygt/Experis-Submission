// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperisCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values
AExperisCharacter::AExperisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	Health = DefaultHealth;
}

// Called when the game starts or when spawned
void AExperisCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	

	//Add the input Mapping Context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}

	

}

//modify player health by the passed in damage ammount and broadcast the players death if/when it occurs
float AExperisCharacter::TakeDamage(float DamageAmount, AActor* DamageCauser)
{
	Health -= DamageAmount;
	
	
	if(DamageAmount > Health)
	{
		Health = 0;
	}else if(Health >= 20)
	{
		Health = 20;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	if(Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("YOU DIED"));
		PlayerDeath.Broadcast();
		IsDead = true;
	}

	return DamageAmount;
}

void AExperisCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementVector.X);
}

void AExperisCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

// Called every frame
void AExperisCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input using the new enhanced input controlls 
void AExperisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AExperisCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExperisCharacter::Look);
	}

}

