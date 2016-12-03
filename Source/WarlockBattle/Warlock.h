// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Warlock.generated.h"

class UWarlockAnimInstance;

UCLASS()
class WARLOCKBATTLE_API AWarlock : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetForward(float intensity);
	void SetBackward(float intensity);
	void SetRight(float intensity);
	void SetLeft(float intensity);
	void SetAttack(bool value);
	void SetLookAtDirection(FVector direction);

private:
	AWarlock();

	virtual void Tick(float DeltaSeconds) override;
	
	FVector CalculateMovementVector();
	void RotateMeshTowardDirection(FVector direction, int orientation);
	void RotateSpineTowardDirection(FVector direction, int orientation);

	USkeletalMeshComponent* SkeletalMeshRef;
	UWarlockAnimInstance* WarlockAnimInstance;

	float Forward;
	float Backward;
	float Right;
	float Left;

	float ForwardIntensity;
	float RightIntensity;

	FRotator RotationSpine = FRotator::ZeroRotator;

	bool isAttacking;

	int Orientation;

	FVector ObjectiveMovementDirection;
	FVector CurrentMovementDirection;

	FVector ObjectiveLookAtDirection = FVector::ZeroVector;
	FVector CurrentLookAtDirection = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float ControllerDamping = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float YawRotationCorrection = -90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float YawRotationCorrectionBackward = -270.0f;
};
