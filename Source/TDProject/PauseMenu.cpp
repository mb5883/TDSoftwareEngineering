// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject.h"
#include "PauseMenu.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "TDProjectGameMode.h"

APauseMenu::APauseMenu(const FObjectInitializer& PCIP) : Super(PCIP)
{
	ResumeName = FName(*FString("Resume"));
	OptionName = FName(*FString("Options"));
	QuitLevelName = FName(*FString("Quit Level"));
	QuitGameName = FName(*FString("Quit Game"));

	lowlightColor = FColor::White;
	highlightColor = FColor::Cyan;

	ResumeColor = lowlightColor;
	OptionColor = lowlightColor;
	QuitLevelColor = lowlightColor;
	QuitGameColor = lowlightColor;

	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
	//	 I recommend creating fonts at a high resolution / size like 36
	//			then you can scale down the font as needed to any size of your choice

	// this avoids needing to make multiple fonts for different sizes, but have a high
	// resolution when you use larger font sizes

}

void APauseMenu::DrawHUD()
{
	//Get screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	
	//Position the text such that it is reletive to the screen dimensions
	ResumePosition = FVector2D(.5 * ScreenDimensions.X, .25 * ScreenDimensions.Y);
	OptionPosition = FVector2D(.5 * ScreenDimensions.X, .4 * ScreenDimensions.Y);
	QuitLevelPosition = FVector2D(.5 * ScreenDimensions.X, .55 * ScreenDimensions.Y);
	QuitGamePosition = FVector2D(.5 * ScreenDimensions.X, .7 * ScreenDimensions.Y);
	Super::DrawHUD();

	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		// Produce a black overlay
		FCanvasTileItem TileItem(FVector2D(0.0f, 0.0f), FVector2D(Canvas->ClipX, Canvas->ClipY), FLinearColor(0.0f, 0.0f, 0.0f, 0.3f));
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);


		//Resume Button 
		DrawText(ResumeName.ToString(), ResumePosition - .5 * ScreenDimensions, HUDFont, FVector2D(1, 1), ResumeColor);
		AddHitBox(ResumePosition - FVector2D(.125 * ScreenDimensions.X, .05 * ScreenDimensions.Y), FVector2D(.25*ScreenDimensions.X, .1 * ScreenDimensions.Y), ResumeName, false);

		//Options Button
		DrawText(OptionName.ToString(), OptionPosition - .5 * ScreenDimensions, HUDFont, FVector2D(1, 1), OptionColor);
		AddHitBox(OptionPosition - FVector2D(.125 * ScreenDimensions.X, .05 * ScreenDimensions.Y), FVector2D(.25*ScreenDimensions.X, .1 * ScreenDimensions.Y), OptionName, true);

		//Quit Level Button
		DrawText(QuitLevelName.ToString(), QuitLevelPosition - .5 * ScreenDimensions, HUDFont, FVector2D(1, 1), QuitLevelColor);
		AddHitBox(QuitLevelPosition - FVector2D(.125 * ScreenDimensions.X, .05 * ScreenDimensions.Y), FVector2D(.25*ScreenDimensions.X, .1 * ScreenDimensions.Y), QuitLevelName, true);

		//Quit Game Button
		DrawText(QuitGameName.ToString(), QuitGamePosition - .5 * ScreenDimensions, HUDFont, FVector2D(1, 1), QuitGameColor);
		AddHitBox(QuitGamePosition - FVector2D(.125 * ScreenDimensions.X, .05 * ScreenDimensions.Y), FVector2D(.25*ScreenDimensions.X, .1 * ScreenDimensions.Y), QuitGameName, true);
	}

}

void APauseMenu::ShowHUD()
{
	Super::ShowHUD();
}

void APauseMenu::NotifyHitBoxClick(FName BoxName)
{
	//Handles events based on what was clicked
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	if (BoxName.ToString() == ResumeName.ToString())
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	if (BoxName.ToString() == QuitGameName.ToString())
	{
		MyController->ConsoleCommand("quit");
	}
}

void APauseMenu::NotifyHitBoxBeginCursorOver(FName BoxName)
{
	//Hightlight the current menu option that is being selected
	if (BoxName.ToString() == ResumeName.ToString())
	{
		ResumeColor = highlightColor;
	}
	else if (BoxName.ToString() == OptionName.ToString())
	{
		OptionColor = highlightColor;
	}
	else if (BoxName.ToString() == QuitLevelName.ToString())
	{
		QuitLevelColor = highlightColor;
	}
	else if (BoxName.ToString() == QuitGameName.ToString())
	{
		QuitGameColor = highlightColor;
	}
}

void APauseMenu::NotifyHitBoxEndCursorOver(FName BoxName)
{
	//De-Hightlight the current menu option that was being selected
	if (BoxName.ToString() == ResumeName.ToString())
	{
		ResumeColor = lowlightColor;
	}
	else if (BoxName.ToString() == OptionName.ToString())
	{
		OptionColor = lowlightColor;
	}
	else if (BoxName.ToString() == QuitLevelName.ToString())
	{
		QuitLevelColor = lowlightColor;
	}
	else if (BoxName.ToString() == QuitGameName.ToString())
	{
		QuitGameColor = lowlightColor;
	}
}



