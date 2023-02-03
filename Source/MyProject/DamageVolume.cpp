// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageVolume.h"
#include "DrawDebugHelpers.h"
#include "Engine/BrushShape.h"
#include "Kismet/GameplayStatics.h"

//#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, VolumeColor,String)

ADamageVolume::ADamageVolume()
{
	//Bind functions to built in events
	OnActorBeginOverlap.AddDynamic(this, &ADamageVolume::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ADamageVolume::OnEndOverlap);
	


	damageSpecVar = damageSpecifier::Default;
}

//a function that is bound to Player death  
void ADamageVolume::Reset()
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Died!"));

}

void ADamageVolume::BeginPlay()
{
	Super::BeginPlay();

	//AExperisCharacter* ExpChar = nullptr;
	//AActor* Character = UGameplayStatics::GetActorOfClass(GetWorld(), AExperisCharacter::StaticClass());

	//if (ExpChar == Cast<AExperisCharacter>(Character))
	//{
		
	//}

	DrawDebugBox(GetWorld(), GetActorLocation(), Brush->Bounds.BoxExtent, VolumeColor, true, -1, 0, 5);
}

void ADamageVolume::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor && (OtherActor != this))
	{
		//PrintString("Overlapp Begin");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Begin Overlap"));
	}

	

	if (AExperisCharacter* Player = Cast<AExperisCharacter>(OtherActor))
	{

		if (!isBound)
		{
			Player->PlayerDeath.AddDynamic(this, &ADamageVolume::Reset);
			isBound = true;
		}
	switch (damageSpecVar)
	{
	case damageSpecifier::Default:
		Player->TakeDamage(5, this);
		break;
	
	case damageSpecifier::Heal:
		Player->TakeDamage(-5, this);
		break;

	case damageSpecifier::Kill:
		Player->TakeDamage(Player->DefaultHealth, this);
		break;

	case damageSpecifier::OneThird:
		Player->TakeDamage(Player->DefaultHealth/3, this);
		break;

	}
		
	}
}

void ADamageVolume::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		//PrintString("Overlapp End");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Overlap!"));
	}
}
