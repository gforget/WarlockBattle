// Fill out your copyright notice in the Description page of Project Settings.

#include "WarlockBattle.h"
#include "Warlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarlockAnimInstance.h"
#include "Runtime/Core/Public/Math/Vector.h"

// Sets default values
AWarlock::AWarlock()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

// Called when the game starts or when spawned
void AWarlock::BeginPlay()
{
	Super::BeginPlay();
	SkeletalMeshRef = this->GetMesh();
	
	WarlockAnimInstance = Cast<UWarlockAnimInstance>(SkeletalMeshRef->GetAnimInstance());
	CurrentLookAtDirection = SkeletalMeshRef->GetRightVector();
}

// Called every frame
void AWarlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	MovementDirection = CalculateMovementVector();

	GetCharacterMovement()->AddInputVector(MovementDirection);

	CurrentLookAtDirection = FVector
	(
	    CurrentLookAtDirection.X + (ObjectiveLookAtDirection.X - CurrentLookAtDirection.X)*RotationDamping,
	    CurrentLookAtDirection.Y + (ObjectiveLookAtDirection.Y - CurrentLookAtDirection.Y)*RotationDamping,
	    CurrentLookAtDirection.Z + (ObjectiveLookAtDirection.Z - CurrentLookAtDirection.Z)*RotationDamping
	);

	FRotator LookAtRotation = RotateMeshTowardDirection(CurrentLookAtDirection);

	FRotator movementRotation = GetCharacterMovement()->Velocity.Rotation();
	movementRotation.Yaw -= 90.0f;

	ObjectiveDirection = FRotator::NormalizeAxis((movementRotation - LookAtRotation).Yaw);

	// if the warlock anim instance is not found break
	if (WarlockAnimInstance == nullptr) return;

	ObjectiveDirection *= -1.0f;

	if (FMath::Abs(ObjectiveDirection) > 135.0f)
	{
		ObjectiveSpeed = GetCharacterMovement()->Velocity.Size()*-1.0f;
		if (ObjectiveDirection > 0)
		{
			ObjectiveDirection = 90.0f - (ObjectiveDirection - 90.0f);
		}
		else
		{
			ObjectiveDirection = -90.0f + ((ObjectiveDirection + 90.0f)*-1.0f);
		}
	}
	else 
	{
		ObjectiveSpeed = GetCharacterMovement()->Velocity.Size();		
	}

	CurrentSpeed = CurrentSpeed + (ObjectiveSpeed - CurrentSpeed)*SpeedDamping;
	CurrentDirection = CurrentDirection + (ObjectiveDirection - CurrentDirection)*RotationDamping;

	WarlockAnimInstance->Speed = CurrentSpeed;
	WarlockAnimInstance->Direction = CurrentDirection;
	WarlockAnimInstance->IsAttacking = IsAttacking;
}

FRotator AWarlock::RotateMeshTowardDirection(FVector direction)
{
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), this->GetActorLocation() + direction);
	FRotator FinalRotator = FRotator(0.0f, LookAtRotator.Yaw + YawRotationCorrection, 0.0f);
	SkeletalMeshRef->SetWorldRotation(FinalRotator);
	return FinalRotator;
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
	IsAttacking = value;
}

void AWarlock::SetLookAtDirection(FVector direction)
{
	ObjectiveLookAtDirection = direction;
}