
#include "TDProject.h"
#include "CharacterTower.h"


// Sets default values
ACharacterTower::ACharacterTower()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;	//Immune to attacks from other towers

	//Add the functionality needed to intercept mouse events
	OnClicked.AddDynamic(this, &ACharacterTower::OnClick );
	OnReleased.AddDynamic(this, &ACharacterTower::OnRelease);
	OnBeginCursorOver.AddDynamic(this, &ACharacterTower::OnBeginCursor);
	OnEndCursorOver.AddDynamic(this, &ACharacterTower::OnEndCursor);	
}

// Called when the game starts or when spawned
void ACharacterTower::BeginPlay()
{
	Super::BeginPlay();	
	P1Controller = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void ACharacterTower::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (bFollowCursor)
	{
		//Get the location relative to where the mouse is pointing 
		FHitResult hit;
		P1Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);
		SetActorRelativeLocation(FVector(hit.Location.X, hit.Location.Y, GetActorLocation().Z));
	}
	else
	{
		//If an enemy is within a certain radius, attack and begin a cooldown timer for the next attack
	}
}

void ACharacterTower::OnClick()
{
	bFollowCursor = true;
}
void ACharacterTower::OnRelease()
{
	//If the placement is valid, then we can let go of mouse control
	bFollowCursor = false;
}

void ACharacterTower::OnBeginCursor()
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse Detected"));
}

void ACharacterTower::OnEndCursor()
{

}
