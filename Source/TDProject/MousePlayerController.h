// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()

	AMousePlayerController(const FObjectInitializer& ObjectInitializer);

	/*
	* Sets up player inputs
	*/
	virtual void SetupInputComponent() override;

	/**
	* Called via input to allow the player to take a break
	*/
	void LevelPause();
};
