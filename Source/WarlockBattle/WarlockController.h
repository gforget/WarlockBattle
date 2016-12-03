// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "WarlockController.generated.h"

class AWarlock;

UCLASS()
class WARLOCKBATTLE_API AWarlockController : public APlayerController
{
	GENERATED_BODY()

	private:

	AWarlockController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetupInput();
	void MoveForward(float intensity);
	void MoveBackward(float intensity);
	void MoveRight(float intensity);
	void MoveLeft(float intensity);
	void AttackPress();
	void AttackRelease();
	
	FVector MouseLookAtDirection();

	bool EveryPointerIsValid = false; //TODO find a way to cancel tick in the editor
	AWarlock* warlock;

};
