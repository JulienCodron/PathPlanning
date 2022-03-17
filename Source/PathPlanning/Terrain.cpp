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
	while (std::getline(file, line))
	{
		x += 50;
		int y = 0;
		for (char c : line)
		{
			y += 50;
			switch (c)
			{
			case '1':
				GenerateWall(x - 25, y - 25);
				break;

			default:
				break;
			}
		}
	}
}
file.close();
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

bool ATerrain::InMatrix(std::tuple<int,int> voisin) 
{
	return std::get<0>(voisin) >= 0 && std::get<0>(voisin) <= matrix.Num() && std::get<0>(voisin) >= 0 && std::get<0>(voisin) <= matrix[0].Num();
}

bool ATerrain::ContainsNoeud(TArray<Noeud> list, Noeud v)
{
	for (Noeud n : list)
	{
		if (n.x == v.x, n.y == v.y, n.heuristique == v.heuristique)
		{
			return true;
		}
	}
	return false;
}

bool ATerrain::ContainsCloserH(TArray<Noeud> list, Noeud v)
{
	for (Noeud n : list)
	{

	}
	return false;
}

void ATerrain::SortListNoeud(TArray<Noeud> &list)
{
	Noeud min = list[0];
	for (Noeud n : list)
	{
		if (n.cout + n.heuristique < min.cout + min.heuristique) min = n;
	}
	Swap(min, list[0]);
}

TArray<Noeud> ATerrain::PathFinding(Noeud depart, Noeud objectif)
{
	/*closedList = File()
	   openList = FilePrioritaire(comparateur = compareParHeuristique)
	   openList.ajouter(depart)
	   tant que openList n'est pas vide
		   u = openList.defiler()
		   si u.x == objectif.x et u.y == objectif.y
			   reconstituerChemin(u)
			   terminer le programme
		   pour chaque voisin v de u dans g
			   si non(   v existe dans closedList
							ou v existe dans openList avec un coût inférieur)
					v.cout = u.cout +1
					v.heuristique = v.cout + distance([v.x, v.y], [objectif.x, objectif.y])
					openList.ajouter(v)
		   closedList.ajouter(u)
	   terminer le programme (avec erreur)*/

	   //verifier si x/y pas un mur, sinon trouver la case la plus close du mur et dans la direction du perso puis relancer foncion sur ces coord
	   //a* voir cours
	   //mettre le plus petit en first a chaque boucle
	TArray<Noeud> closedList = {};
	TArray<Noeud> openList = {};
	TArray<std::tuple<int,int>> voisins;
	openList.Add(depart);
	while (openList.Num() != 0)
	{
		Noeud n = openList[0];
		voisins = { {n.x + 1,n.y},{n.x - 1,n.y},{n.x,n.y + 1},{n.x,n.y - 1} };
		if (n.x == objectif.x && n.y == objectif.y)
		{
			TArray<Noeud> path;
			path.Add(n);
			while (n.Parent != NULL)
			{
				path.Add(n);
				n = *n.Parent;
			}
			return path;
		}
		for (std::tuple<int, int> voisin : voisins)
		{
			if (InMatrix(voisin))
			{
				int x = std::get<0>(voisin);
				int y = std::get<1>(voisin);
				Noeud v = { x, y, n.cout+1, Manhattan(x,y,objectif.x,objectif.y), &n};
				if (!ContainsNoeud(closedList,v) || ContainsCloserH(openList,v))
				{
					openList.Add(v);
				}
			}
		}
		closedList.Add(n);
		SortListNoeud(openList);
	}
	return TArray<Noeud>();
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

