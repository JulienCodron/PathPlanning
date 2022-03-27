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

	matrix.SetNum(20);
	for (int i = 0; i < 20; i++) {
		matrix[i].Init(1, 20);
	}

	std::ifstream file;
	std::string dir = TCHAR_TO_UTF8(*FPaths::ProjectContentDir());
	std::string fileName = dir + "Map/MapTxt/DefaultMap.txt";
	file.open(fileName);


	if (file.is_open())
	{
		int x = 0;
		std::string line;
		while (std::getline(file, line))
		{
			int y = 0;
			for (char c : line)
			{
				switch (c)
				{
				case '1':
					GenerateWall(x*50 + 25 , y*50 + 25);
					if (x >= 0 && x <= 19 && y >= 0 && y <= 19) matrix[x][y] = 1;
					break;
				case ',':
					break;
				default:
					if (x >= 0 && x <= 19 && y >= 0 && y <= 19) matrix[x][y] = 0;
					break;
				}	
				y += 1;
			}
			x += 1;
		}
	}
	file.close();
	/*for (int x = 0; x < matrix.Num(); ++x)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Red, FString::Printf(TEXT("%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d"), matrix[x][0], matrix[x][1], matrix[x][2], matrix[x][3], matrix[x][4], matrix[x][5], matrix[x][6], matrix[x][7], matrix[x][8], matrix[x][9], matrix[x][10], matrix[x][11], matrix[x][12], matrix[x][13], matrix[x][14], matrix[x][15], matrix[x][16], matrix[x][17], matrix[x][18], matrix[x][19]));
	}*/
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


int ATerrain::compareHeuristique(Noeud n1, Noeud n2)
{
	if (n1.heuristique < n2.heuristique) return 1;
	else if (n1.heuristique == n2.heuristique) return 0;
	return -1;
}

int ATerrain::Manhattan(int x1, int y1, int x2, int y2)
{
	int x_dif, y_dif;

	x_dif = x2 - x1;
	y_dif = y2 - y1;
	if (x_dif < 0)
		x_dif = -x_dif;
	if (y_dif < 0)
		y_dif = -y_dif;
	return  x_dif + y_dif;
}

bool ATerrain::isValid(int x, int y)
{
	if (x >= 0 && x < matrix.Num() && y >= 0 && y < matrix[0].Num())
	{
		return matrix[x][y] == 0;
	}
	return false;
}

bool ATerrain::ContainsNoeud(TArray<Noeud> list, Noeud v)
{
	for (Noeud n : list)
	{
		if (n.x == v.x && n.y == v.y)
		{
			return true;
		}
	}
	return false;
}

bool ATerrain::ContainsCloserH(TArray<Noeud*> list, Noeud v)
{
	for (Noeud * n : list)
	{
		if (n->x == v.x, n->y == v.y && n->cout < v.cout ) return true;
	}
	return false;
}

void ATerrain::SortListNoeud(TArray<Noeud*> &list)
{
	if (list.Num() > 0)
	{
		Noeud *min = list[0];
		int index = 0;
		for (int x = 0; x < list.Num(); ++x)
		{
			if (list[x]->cout + list[x]->heuristique < min->cout + min->heuristique) {
				index = x;
				min = list[x];
			}
		}
		Swap(list[index], list[0]);
	}	
}

void ATerrain::RemoveFirstNode(TArray<Noeud*>& list)
{
	Swap(list[list.Num() - 1], list[0]);
	list.Pop();
}

TArray<int> ATerrain::PathFinding(Noeud depart, Noeud objectif)
{
	//verifier si x/y pas un mur, sinon trouver la case la plus close du mur et dans la direction du perso puis relancer foncion sur ces coord
	
	if(!isValid(objectif.x,objectif.y)) return TArray<int>();
	TArray<Noeud> closedList = {};
	TArray<Noeud*> openList = {};
	TArray<std::tuple<int,int>> voisins;
	openList.Add(new Noeud(depart));
	SortListNoeud(openList);

	while (openList.Num() != 0)
	{
		Noeud * n = openList[0];
		if (n->x == objectif.x && n->y == objectif.y)
		{
			TArray<int> path;
			Noeud* childNode;
			while (n->Parent != nullptr && n->Parent != NULL)
			{
				path.Add(n->movement);				
				childNode = n;
				n = n->Parent;
				delete(childNode);
			}
			return path;
		}

		voisins = { {n->x + 1,n->y},{n->x,n->y + 1} ,{n->x - 1,n->y}, {n->x,n->y - 1} };
		int i = 0;
		for (std::tuple<int, int> voisin : voisins)
		{
			int x = std::get<0>(voisin);
			int y = std::get<1>(voisin);
			if (isValid(x,y))
			{
				Noeud * v = new Noeud{ x, y, n->cout, Manhattan(x,y,objectif.x,objectif.y), n , i};
				if (!(ContainsNoeud(closedList,*v) || ContainsCloserH(openList,*v)))
				{
					openList.Add(v);
				}
			}
			i++;
		}
		RemoveFirstNode(openList);
		SortListNoeud(openList);
		closedList.Add(*n);
	}
	return TArray<int>();
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

