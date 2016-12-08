// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "WarlockAnimInstance.generated.h"
class AWarlock;

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class WARLOCKBATTLE_API UWarlockAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	bool IsAttacking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	float AnimationRate;

	UPROPERTY(EditAnywhere, Category = "Animation Elements")
	UAnimMontage* PrimaryAttackMontage;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	virtual void NativeInitializeAnimation() override;
};
