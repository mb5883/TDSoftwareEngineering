// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API APauseMenu : public AHUD
{
	GENERATED_BODY()

	//Variable to represent the font
	UPROPERTY()
	UFont* HUDFont;

	FName ResumeName;			//Resume the game
	FName OptionName;			//Access options
	FName QuitLevelName;			//Exit the current level
	FName QuitGameName;			//Quit the game

	/*Placements for hitbox and text*/
	FVector2D ResumePosition;	
	FVector2D OptionPosition;	
	FVector2D QuitLevelPosition;
	FVector2D QuitGamePosition;

	/*Colors to represent each of the options*/
	FColor ResumeColor;
	FColor OptionColor;
	FColor QuitLevelColor;
	FColor QuitGameColor;
public:
	/*Colors when highlighted and not*/
	FColor lowlightColor;
	FColor highlightColor;
	APauseMenu(const FObjectInitializer& PCIP);
	//This method will draw the UI we need
	virtual void DrawHUD() override;

	//Chooses whether or not to diplay the UI
	virtual void ShowHUD() override;

	//Event that handles the on mouse clicked
	virtual void NotifyHitBoxClick(FName BoxName) override;

	//Event triggers on MouseEnter
	virtual void NotifyHitBoxBeginCursorOver(FName BoxName) override;

	//Event triggers on MouseExit
	virtual void NotifyHitBoxEndCursorOver(FName BoxName) override;
	
	
	
};
