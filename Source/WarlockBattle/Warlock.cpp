// Fill out your copyright notice in the Description page of Project Settings.

#include "WarlockBattle.h"
#include "Warlock.h"


// Sets default values
AWarlock::AWarlock()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWarlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AWarlock::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

