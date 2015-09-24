// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject.h"
#include "TDProjectGameMode.h"
#include "TowerPurchaseHud.h"


ATDProjectGameMode::ATDProjectGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HUDClass = ATowerPurchaseHud::StaticClass();
}
