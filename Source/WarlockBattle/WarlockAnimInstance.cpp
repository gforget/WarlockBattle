// Fill out your copyright notice in the Description page of Project Settings.

#include "WarlockBattle.h"
#include "WarlockAnimInstance.h"
#include "Warlock.h"

void UWarlockAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (PrimaryAttackMontage == nullptr) return;
	if (IsAttacking){
		Montage_Play(PrimaryAttackMontage);
	}

}

void UWarlockAnimInstance::NativeInitializeAnimation()
{
	//Very Important Line
	Super::NativeInitializeAnimation();
}
