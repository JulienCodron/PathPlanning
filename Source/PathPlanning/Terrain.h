// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

UCLASS()
class PATHPLANNING_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	TArray<TArray<int>> matrix;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GenerateWall(int x, int y);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TArray<int> PathFinding(int x, int y);

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Wall)
		TSubclassOf<class AWall> WallClass;

};
