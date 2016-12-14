// Fill out your copyright notice in the Description page of Project Settings.

#include "WarlockBattle.h"
#include "WarlockController.h"
#include "Warlock.h"

AWarlockController::AWarlockController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void AWarlockController::BeginPlay()
{
	Super::BeginPlay();
	warlock = Cast<AWarlock>(GetCharacter());
	if (warlock == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("warlock not found"));
		return;
	}

	EveryPointerIsValid = true;
	SetupInput();
}

void AWarlockController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!EveryPointerIsValid) return;
	warlock->SetLookAtDirection(MouseLookAtDirection());
}

FVector AWarlockController::MouseLookAtDirection()
{

	float MouseLocationX;
	float MouseLocationY;

	GetMousePosition(MouseLocationX, MouseLocationY);

	FVector WorldLocation;
	FVector WorldDirection;

	DeprojectScreenPositionToWorld(MouseLocationX, MouseLocationY, WorldLocation, WorldDirection);

	FHitResult OutHit;
	FVector Start = WorldLocation;
	FVector End = WorldDirection*10000.0f + WorldLocation;
	FVector HitLocation;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Camera))
	{
		HitLocation = OutHit.Location;
	}
	else
	{
		return FVector::ZeroVector;
	}

	return (HitLocation - warlock->GetActorLocation()).GetSafeNormal();
}

void AWarlockController::SetupInput()
{
	InputComponent->BindAxis("Forward", this, &AWarlockController::MoveForward);
	InputComponent->BindAxis("Backward", this, &AWarlockController::MoveBackward);
	InputComponent->BindAxis("Right", this, &AWarlockController::MoveRight);
	InputComponent->BindAxis("Left", this, &AWarlockController::MoveLeft);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AWarlockController::AttackPress);
	InputComponent->BindAction("Attack", IE_Released, this, &AWarlockController::AttackRelease);
}

void AWarlockController::MoveForward(float intensity)
{
	//UE_LOG(LogTemp, Warning, TEXT("forward intensity %f"), intensity);
	warlock->SetForward(intensity);
}

void AWarlockController::MoveBackward(float intensity)
{
	//UE_LOG(LogTemp, Warning, TEXT("forward intensity %f"), intensity);
	warlock->SetBackward(intensity);
}

void AWarlockController::MoveRight(float intensity)
{
	warlock->SetRight(intensity);
}

void AWarlockController::MoveLeft(float intensity)
{
	warlock->SetLeft(intensity);
}

void AWarlockController::AttackPress() 
{
	warlock->SetAttack(true);
}

void AWarlockController::AttackRelease()
{
	warlock->SetAttack(false);
}
