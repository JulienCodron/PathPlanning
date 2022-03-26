// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

typedef struct _Noeud {
	int x;
	int y;
	int cout;
	int heuristique;
	struct _Noeud  * Parent = nullptr;
	int movement;
}Noeud;

UCLASS()
class PATHPLANNING_API ATerrain : public AActor
{
	GENERATED_BODY()

	int compareHeuristique(Noeud n1, Noeud n2);
	bool isValid(int x, int y);
	bool ContainsNoeud(TArray<Noeud> list, Noeud v);
	bool ContainsCloserH(TArray<Noeud*> list, Noeud v);
	void SortListNoeud(TArray<Noeud*>& list);
	void RemoveFirstNode(TArray<Noeud*>& list);


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
	TArray<int> PathFinding(Noeud depart, Noeud objectif);

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Wall)
		TSubclassOf<class AWall> WallClass;

	int Manhattan(int x1, int y1, int x2, int y2);
};
