
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
		CheckAutoAttack();
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

void ACharacterTower::CheckAutoAttack()
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);	//We don't want to trigger attack ourselves

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
		UE_LOG(LogTemp, Warning, TEXT("Attack %s"), *(characterName.ToString()));
		bIsAutoAttackReady = false;
		GetWorldTimerManager().SetTimer(autoAttackTimer, this, &ACharacterTower::EndAutoAttackCooldown, baseFirerate);
	}
	
}

void ACharacterTower::EndAutoAttackCooldown()
{
	bIsAutoAttackReady = true;
	overlaps.Empty();
}