// Fill out your copyright notice in the Description page of Project Settings.


#include "Stearing_Npc.h"


// Called when the game starts or when spawned
AStearing_Npc::AStearing_Npc()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AStearing_Npc::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStearing_Npc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AStearing_Npc::AddCheckPoint(int i, FVector spawnpos) {
	switch (i)
	{
	case 0: //haut
		spawnpos.X += 50;
		break;
	case 1: //droite
		spawnpos.Y += 50;
		break;
	case 2: //bas
		spawnpos.X -= 50;
		break;
	case 3: //gauche
		spawnpos.Y -= 50;
		break;
	default:
		break;
	}
	AActor* cp = GetWorld()->SpawnActor<AActor>(CheckPoint, spawnpos, GetActorRotation());
	CurrentCircuit.Add(cp);
	return spawnpos;
}
