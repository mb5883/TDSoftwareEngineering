/*
This is for the most part superior to character tower since it can modify the flipbook and the sprite; 
however intellisense(automatic syntax checker) isn't working for properly for this source code so it is showing errors that it shouldn't
therefore, both the original version and this version which handles sprites
*/

#include "TDProject.h"
#include "PaperCharacterTower.h"


// Sets default values
APaperCharacterTower::APaperCharacterTower()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;	//Immune to attacks from other towers


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
		CheckAutoAttack();
		
	}
}

void APaperCharacterTower::OnClick()
{
	bFollowCursor = true;
	GetRenderComponent()->SetSpriteColor(FLinearColor::White);
}
void APaperCharacterTower::OnRelease()
{
	//If the placement is valid, then we can let go of mouse control
	bFollowCursor = false;
}

void APaperCharacterTower::OnBeginCursor()
{
	GetRenderComponent()->SetSpriteColor(FLinearColor::Green);
}

void APaperCharacterTower::OnEndCursor()
{
	GetRenderComponent()->SetSpriteColor(FLinearColor::White);
}

void APaperCharacterTower::CheckAutoAttack()
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	//CollisionParams.AddIgnoredActor(ACharacterTower);
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
		CollisionParams);

	bool isEnemy = false;
	for (int32 i = 0; i < overlaps.Num(); i++)
	{
		/*
		Replace ACharacter with appropriate enemy class
		Make sure to make a generic enemy class that other enemy types based off of if you want to minimize the workload
		*/
		ACharacter* enemy = Cast<ACharacter>(overlaps[i].GetActor());
		if (enemy != nullptr)
		{
			isEnemy = true;
		}
	}
	if (isEnemy && bIsAutoAttackReady)
	{
		bIsAutoAttackReady = false;
		GetRenderComponent()->SetFlipbook(attackAnimation);
		GetWorldTimerManager().SetTimer(autoAttackTimer, this, &APaperCharacterTower::EndAutoAttackCooldown, baseFirerate);
		
	}
	else if (!isEnemy && bIsAutoAttackReady)
	{
		GetRenderComponent()->SetFlipbook(idleAnimation);
	}
	
}

void APaperCharacterTower::EndAutoAttackCooldown()
{
	bIsAutoAttackReady = true;
	overlaps.Empty();
}