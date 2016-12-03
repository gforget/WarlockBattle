// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "WarlockAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WARLOCKBATTLE_API UWarlockAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	public:

	/** Is Moving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	bool IsAttacking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Property")
	FRotator SpineRotation;
};
