// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookActor.h"
#include "GameFramework/Actor.h"
#include "PaperCharacterTower.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API APaperCharacterTower : public APaperFlipbookActor
{
	GENERATED_BODY()

private:
	bool bFollowCursor = false;		//Is the object currently tracking the cursor
	bool bIsValidPlacement = true;  //Is the object allowed to be placed where the mouse cursor is
	bool bIsAutoAttackReady = true; //Checks to see if it is possible to autoattack
	APlayerController* P1Controller; //Get the first player's controller since it controls the mouse functions
	TArray<FOverlapResult> overlaps; //Stores all objects within a radius of attack

	FTimerHandle autoAttackTimer;	// Timer when the character can attack again
public:

	UPROPERTY(EditAnywhere, Category = Characteristics)
		FName characterName;
	//Each character has base stats which with other modifications convert to
	UPROPERTY(EditAnywhere, Category = Characteristics)
		int32 baseAutoAttackDamage;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		int32 baseAggroRadius;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		int32 basePurchaseCost;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		int32 currentLevel;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		float baseFirerate;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		float baseProjectileSpeed;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		float animationRate;
	UPROPERTY(EditAnywhere, Category = Characteristics)
		UPaperFlipbook* idleAnimation;

	UPROPERTY(EditAnywhere, Category = Characteristics)
		UPaperFlipbook* attackAnimation;

	// Sets default values for this actor's properties
	APaperCharacterTower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Called when it is clicked on by the mouse
	UFUNCTION()
	void OnClick();

	//Called when it is released by the mouse
	UFUNCTION()
	void OnRelease();

	//Called when it is hovering over by the mouse
	UFUNCTION()
	void OnBeginCursor();

	//Called when it is mouse cursor is no longer on it
	UFUNCTION()
	void OnEndCursor();


	//Called to check an enemy is within attacking range
	void CheckAutoAttack();

	//called to reactivate autoattack
	void EndAutoAttackCooldown();
};
