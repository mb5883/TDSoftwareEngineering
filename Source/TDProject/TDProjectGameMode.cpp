// This sets the main settings for the game

#include "TDProject.h"
#include "TDProjectGameMode.h"
#include "TowerPurchaseHud.h"
#include "PauseMenu.h"
#include "MousePlayerController.h"

ATDProjectGameMode::ATDProjectGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = NULL; //otherwise a pawn will spawn
	HUDClass = APauseMenu::StaticClass(); //Default hud is the pause menu, multiple huds can't be set this way
	PlayerControllerClass = AMousePlayerController::StaticClass(); //Sets up the proper controller
	NumPlayers = 1;
	NumSpectators = 0;
}
