// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Wall.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	int x = 50;
	matrix.SetNum(50);

	for (int i = 0; i < x; i++) {
		matrix[i].Init(1, 50);
	}

	std::ifstream file;
	std::string dir = TCHAR_TO_UTF8(*FPaths::ProjectContentDir());
	std::string fileName = dir + "Map/MapTxt/DefaultMap.txt";
	file.open(fileName);


	if (file.is_open())
	{
		x = 0;
		std::string line;
		while (std::getline(file,line))
		{
			x += 50;
			int y = 0;
			for (char c : line) 
			{
				y += 50;
				switch (c)
				{
					case '1':
						GenerateWall(x-25,y-25);
						break;

					default:
						break;
				}
			}
		}
	}

	file.close();


	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), matrix[0].Num()));

}

void ATerrain::GenerateWall(int x, int y)
{
	if (WallClass == nullptr) return;

	FVector SpawnLocation = this->GetActorLocation();
	SpawnLocation.X += x;
	SpawnLocation.Y += y;

	FTransform SpawnTransform(this->GetActorRotation(), SpawnLocation);
	AWall* Wall = GetWorld()->SpawnActor<AWall>(WallClass, SpawnTransform);
	Wall->FinishSpawning(SpawnTransform);
}

TArray<int> ATerrain::PathFinding(int x, int y)
{
	//verifier si x/y pas un mur, sinon trouver la case la plus close du mur et dans la direction du perso puis relancer foncion sur ces coord
	//a* voir cours

	return TArray<int>();
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

