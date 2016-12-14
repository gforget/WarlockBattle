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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	FRotator SpineRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	float Speed;

	//UFUNCTION(Category = "Character Action", BlueprintImplementableEvent, BlueprintCallable)
	//void Attack1(bool);

private:
	AWarlock();

	virtual void Tick(float DeltaSeconds) override;
	
	FVector CalculateMovementVector();
	FRotator RotateMeshTowardDirection(FVector direction);
	
	USkeletalMeshComponent* SkeletalMeshRef;
	UWarlockAnimInstance* WarlockAnimInstance;

	float Forward;
	float Backward;
	float Right;
	float Left;

	float ForwardIntensity;
	float RightIntensity;

	float CurrentSpeed = 0.0f;
	float ObjectiveSpeed;

	float CurrentDirection = 0.0f;
	float ObjectiveDirection;

	FVector MovementDirection;

	FVector CurrentLookAtDirection;
	FVector ObjectiveLookAtDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float SpeedDamping = 0.25f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float RotationDamping = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = "Warlock Property")
	float YawRotationCorrection = -90.0f;

};
