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
}

// Called every frame
void AWarlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	MovementDirection = CalculateMovementVector();

	//CurrentMovementDirection = FVector
	//(
	//	CurrentMovementDirection.X + (ObjectiveMovementDirection.X - CurrentMovementDirection.X)*ControllerDamping,
	//	CurrentMovementDirection.Y + (ObjectiveMovementDirection.Y - CurrentMovementDirection.Y)*ControllerDamping,
	//	CurrentMovementDirection.Z + (ObjectiveMovementDirection.Z - CurrentMovementDirection.Z)*ControllerDamping
	//);

	//CurrentLookAtDirection = FVector
	//(
	//	CurrentLookAtDirection.X + (ObjectiveLookAtDirection.X - CurrentLookAtDirection.X)*ControllerDamping,
	//	CurrentLookAtDirection.Y + (ObjectiveLookAtDirection.Y - CurrentLookAtDirection.Y)*ControllerDamping,
	//	CurrentLookAtDirection.Z + (ObjectiveLookAtDirection.Z - CurrentLookAtDirection.Z)*ControllerDamping
	//);

	GetCharacterMovement()->AddInputVector(MovementDirection);
	
	FRotator LookAtRotation = RotateMeshTowardDirection(LookAtDirection);
	FRotator movementRotation = GetCharacterMovement()->Velocity.Rotation();
	movementRotation.Yaw -= 90.0f;
	float direction = FRotator::NormalizeAxis((movementRotation - LookAtRotation).Yaw);

	if (WarlockAnimInstance == nullptr) return;

	WarlockAnimInstance->IsAttacking = IsAttacking;
	direction *= -1.0f;

	if (FMath::Abs(direction) > 90.0f)
	{
		ObjectiveSpeed = GetCharacterMovement()->Velocity.Size()*-1.0f;
		//WarlockAnimInstance->Speed = GetCharacterMovement()->Velocity.Size()*-1.0f;
		if (direction > 0)
		{
			direction = 90.0f - (direction - 90.0f);
		}
		else
		{
			direction = -90.0f + ((direction + 90.0f)*-1.0f);
		}

		//UE_LOG(LogTemp, Warning, TEXT("Rotation : %f"), direction);
		WarlockAnimInstance->Direction = direction;
	}
	else 
	{
		ObjectiveSpeed = GetCharacterMovement()->Velocity.Size();
		//WarlockAnimInstance->Speed = GetCharacterMovement()->Velocity.Size();
		WarlockAnimInstance->Direction = direction;
	}

	CurrentSpeed = CurrentSpeed + (ObjectiveSpeed - CurrentSpeed)*ControllerDamping;
	WarlockAnimInstance->Speed = CurrentSpeed;
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
	LookAtDirection = direction;
}