// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Terrain.h"
#include "Stearing_Npc.h"

#include "GameFramework/PlayerController.h"
#include "NPC_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PATHPLANNING_API ANPC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected: 
	virtual void BeginPlay() override;
	int pathToSpawn = 0;

public:
	void SetupInputComponent() override;
	void OnMouseClick();

	ATerrain * terrain;
	AStearing_Npc* character;
};
