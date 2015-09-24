// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject.h"
#include "TowerPurchaseHud.h"

ATowerPurchaseHud::ATowerPurchaseHud(const FObjectInitializer& PCIP) : Super(PCIP)
{
	//static ConstructorHelpers::FClassFinder<AActor> PlayerPawnBPClass(TEXT("/Game/Content/BluePrints/testText"));
}
void ATowerPurchaseHud::ShowHUD()
{
	Super::ShowHUD();
}
void ATowerPurchaseHud::NotifyHitBoxBeginCursorOver(FName BoxName)
{

}
void ATowerPurchaseHud::NotifyHitBoxClick(FName BoxName)
{

}
void ATowerPurchaseHud::DrawHUD()
{
	Super::DrawHUD();
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	
	FCanvasTileItem TileItem(FVector2D(0.0f, 0.0f), FVector2D(Canvas->ClipX / 7.0, Canvas->ClipY), FLinearColor(0.0f, 0.0f, 0.0f, 0.3f));
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
	
}
void ATowerPurchaseHud::NotifyHitBoxEndCursorOver(FName BoxName)
{

}


