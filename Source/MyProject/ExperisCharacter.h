// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ExperisCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExpCharDeath);

class USpringArmComponent;
class UCameraComponenet;
class UAnimMontage;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MYPROJECT_API AExperisCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExperisCharacter();

	UPROPERTY(BlueprintReadOnly)
	float Health = 0;

	//a check to ensure that the players health reached Zero
	UPROPERTY(BlueprintReadOnly)
		bool IsDead = false;

	float DefaultHealth = 20;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable)
		FExpCharDeath PlayerDeath;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BluePrintCallable)
	void Look(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Advanced input axis mapping setup 
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	


	//void Move(const FInputActionValue& Value);
	//void Look(const FInputActionValue& Value);


	


	
	

	
};
