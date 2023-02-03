// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ExperisCharacter.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "DamageVolume.generated.h"

/**
 * 
 */
//the different variations of the trigger volume to modify health in different ways
UENUM()
enum  damageSpecifier {
	Default,
	Heal,
	Kill,
	OneThird,
};

UCLASS()
class MYPROJECT_API ADamageVolume : public ATriggerVolume
{
	GENERATED_BODY()

	
public:
	//base constructor to set up the default value
	ADamageVolume();

	bool isBound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor VolumeColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<damageSpecifier> damageSpecVar;

	UFUNCTION()
		void Reset();

	virtual void BeginPlay() override;

protected:
	 

	//on begin overlap
	UFUNCTION()
	virtual	void OnBeginOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	//on end overlap
	UFUNCTION()
		void OnEndOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

private:

	
};
