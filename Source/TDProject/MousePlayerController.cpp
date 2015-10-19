// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject.h"
#include "MousePlayerController.h"
#include "PauseMenu.h"

AMousePlayerController::AMousePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAction("LevelPause", IE_Pressed, this, &AMousePlayerController::LevelPause);
}

void AMousePlayerController::LevelPause()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetWorld()->GetAuthGameMode()->HUDClass = APauseMenu::StaticClass();
	UE_LOG(LogTemp, Warning, TEXT("GamePaused"));
}
