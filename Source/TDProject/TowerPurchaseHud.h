// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TowerPurchaseHud.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API ATowerPurchaseHud : public AHUD
{
	GENERATED_BODY()
	
private: 
	TArray<FVector2D> UILocation;
	TArray<FVector2D> UIScale;

public:	

	ATowerPurchaseHud(const FObjectInitializer& PCIP);

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
