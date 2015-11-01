// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject.h"
#include "PaperCharacterTower.h"


// Sets default values
APaperCharacterTower::APaperCharacterTower()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;	//Immune to attacks from other towers

	/*
	MyCollisionComp = CreateDefaultSubobject<USphereComponent>(FName(TEXT("CollisionComponent")));
	MyCollisionComp->RelativeLocation = FVector::ZeroVector;
	MyCollisionComp->SetSphereRadius(20.0f);
	*/

	//Add the functionality needed to intercept mouse events
	OnClicked.AddDynamic(this, &APaperCharacterTower::OnClick);
	OnReleased.AddDynamic(this, &APaperCharacterTower::OnRelease);
	OnBeginCursorOver.AddDynamic(this, &APaperCharacterTower::OnBeginCursor);
	OnEndCursorOver.AddDynamic(this, &APaperCharacterTower::OnEndCursor);
}

// Called when the game starts or when spawned
void APaperCharacterTower::BeginPlay()
{
	Super::BeginPlay();
	P1Controller = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void APaperCharacterTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		GetWorld()->OverlapMultiByChannel(
			//output list
			overlaps,
			//origin location
			this->GetActorLocation(),
			//origin rotation
			FQuat::Identity,
			//collision channel
			ECollisionChannel::ECC_Pawn,
			//collision primitive
			FCollisionShape::MakeSphere(baseAggroRadius),
			//collision parameters
			FCollisionQueryParams());
		
		if (overlaps.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Object Detected within range(paper)"));
		}
	}
}

void APaperCharacterTower::OnClick()
{
	bFollowCursor = true;
}
void APaperCharacterTower::OnRelease()
{
	//If the placement is valid, then we can let go of mouse control
	bFollowCursor = false;
}

void APaperCharacterTower::OnBeginCursor()
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse Detected"));
}

void APaperCharacterTower::OnEndCursor()
{

}
