// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StearingObject.h"
#include "Stearing_Npc.generated.h"

/**
 * 
 */
UCLASS()
class PATHPLANNING_API AStearing_Npc : public AStearingObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStearing_Npc();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
		class USceneComponent* RootScene;
	
	FVector AddCheckPoint(int i, FVector spawnpos);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "MoveActor", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> CheckPoint;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

