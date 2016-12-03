// Fill out your copyright notice in the Description page of Project Settings.

#include "WarlockBattle.h"
#include "Warlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarlockAnimInstance.h"

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
	SkeletalMeshRef = this->GetMesh();
	SkeletalMeshRef->bEnableUpdateRateOptimizations = true;
	
	WarlockAnimInstance = Cast<UWarlockAnimInstance>(SkeletalMeshRef->GetAnimInstance());
	CurrentMovementDirection = SkeletalMeshRef->GetRightVector();
}

// Called every frame
void AWarlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ObjectiveMovementDirection = CalculateMovementVector();
	
	CurrentMovementDirection = FVector
	(
		CurrentMovementDirection.X + (ObjectiveMovementDirection.X - CurrentMovementDirection.X)*ControllerDamping,
		CurrentMovementDirection.Y + (ObjectiveMovementDirection.Y - CurrentMovementDirection.Y)*ControllerDamping,
		CurrentMovementDirection.Z + (ObjectiveMovementDirection.Z - CurrentMovementDirection.Z)*ControllerDamping
	);

	CurrentLookAtDirection = FVector
	(
		CurrentLookAtDirection.X + (ObjectiveLookAtDirection.X - CurrentLookAtDirection.X)*ControllerDamping,
		CurrentLookAtDirection.Y + (ObjectiveLookAtDirection.Y - CurrentLookAtDirection.Y)*ControllerDamping,
		CurrentLookAtDirection.Z + (ObjectiveLookAtDirection.Z - CurrentLookAtDirection.Z)*ControllerDamping
	);

	GetCharacterMovement()->AddInputVector(CurrentMovementDirection);
	
	if (ObjectiveMovementDirection.Size() != 0)
	{
		if (FVector::DotProduct(CurrentMovementDirection, CurrentLookAtDirection) < 0.0f)
		{
			Orientation = -1;
		}
		else 
		{
			Orientation = 1;
		}

		RotateMeshTowardDirection(CurrentMovementDirection, Orientation);
		RotateSpineTowardDirection(CurrentLookAtDirection, Orientation);
	}
	else 
	{
		Orientation = 1;
		if (FVector::DotProduct(SkeletalMeshRef->GetRightVector(), ObjectiveLookAtDirection) < 0.0f)
		{
			RotateMeshTowardDirection(CurrentLookAtDirection, Orientation);
		}
		//RotateMeshTowardDirection(CurrentLookAtDirection, Orientation);
		RotateSpineTowardDirection(CurrentLookAtDirection, Orientation);
	}


	if (WarlockAnimInstance == nullptr) return;
	WarlockAnimInstance->Speed = GetCharacterMovement()->Velocity.Size()*Orientation;
	WarlockAnimInstance->IsAttacking = isAttacking;
	WarlockAnimInstance->SpineRotation = RotationSpine;
}

void AWarlock::RotateSpineTowardDirection(FVector direction, int orientation)
{
	float YawCorrection;
	if (orientation == 1)
	{
		YawCorrection = YawRotationCorrection;
	}
	else
	{
		YawCorrection = 180.0f;
	}

	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), this->GetActorLocation() + direction);
	RotationSpine = FRotator(0.0f, LookAtRotator.Yaw + YawRotationCorrection - SkeletalMeshRef->GetComponentRotation().Yaw, 0.0f);
}

void AWarlock::RotateMeshTowardDirection(FVector direction, int orientation)
{
	float YawCorrection;
	if (orientation == 1)
	{
		YawCorrection = YawRotationCorrection;
	}
	else
	{
		YawCorrection = YawRotationCorrectionBackward;
	}

	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), this->GetActorLocation() + direction);
	FRotator FinalRotator = FRotator(0.0f, LookAtRotator.Yaw + YawCorrection, 0.0f);
	SkeletalMeshRef->SetWorldRotation(FinalRotator);
}

FVector AWarlock::CalculateMovementVector() 
{
	ForwardIntensity = FMath::Abs(Forward + Backward);
	RightIntensity = FMath::Abs(Left + Right);

	return FVector(Forward + Backward, Left + Right, 0.0f).GetSafeNormal();
}

void AWarlock::SetForward(float intensity)
{
	Forward = intensity;
}

void AWarlock::SetBackward(float intensity)
{
	Backward = intensity;
}

void AWarlock::SetRight(float intensity)
{
	Right = intensity;
}

void AWarlock::SetLeft(float intensity)
{
	Left = intensity;
}

void AWarlock::SetAttack(bool value)
{
	isAttacking = value;
}

void AWarlock::SetLookAtDirection(FVector direction)
{
	ObjectiveLookAtDirection = direction;
}