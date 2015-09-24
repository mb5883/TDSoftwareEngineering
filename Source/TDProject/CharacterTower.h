// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CharacterTower.generated.h"

UCLASS()
class TDPROJECT_API ACharacterTower : public AActor
{
	GENERATED_BODY()
	
private:
	bool bFollowCursor = false;		//Is the object currently tracking the cursor
	bool bIsValidPlacement = true;  //Is the object allowed to be placed where the mouse cursor is
	APlayerController* P1Controller; //Get the first player's controller since it controls the mouse functions

public:

	UPROPERTY(EditAnywhere, Category = Characteristics )
	FName characterName;
	//Each character has base stats which with other modifications convert to
	UPROPERTY(EditAnywhere)
	int32 baseAutoAttackDamage;		

	UPROPERTY(EditAnywhere, Category = Characteristics)
	int32 baseAggroRadius;		

	UPROPERTY(EditAnywhere, Category = Characteristics)
	int32 basePurchaseCost;	

	UPROPERTY(EditAnywhere, Category = Characteristics)
	int32 currentLevel;

	UPROPERTY(EditAnywhere, Category = Characteristics)
	double baseFirerate;

	UPROPERTY(EditAnywhere, Category = Characteristics)
	double baseProjectileSpeed;


	// Sets default values for this actor's properties
	ACharacterTower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Called when it is clicked on by the mouse
	void OnClick();

	void OnRelease();

	void OnBeginCursor();

	void OnEndCursor();
	
};
