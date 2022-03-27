// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Terrain.h"

void ANPC_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("MouseClick", IE_Pressed, this, &ANPC_PlayerController::OnMouseClick);
}

void ANPC_PlayerController::BeginPlay()
{
    TArray<AActor*> list;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATerrain::StaticClass(), list);
    if (list.Num() > 0) 
    {
        terrain = Cast<ATerrain>(list[0]);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "No Terrain Found (NPC_PlayerController)");
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStearing_Npc::StaticClass(), list);
    if (list.Num() > 0)
    {
        character = Cast<AStearing_Npc>(list[0]);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "No Character Found (NPC_PlayerController)");
    }
}

void ANPC_PlayerController::OnMouseClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
    FVector location = HitResult.Location;

    if (HitResult.GetComponent() && character!=NULL)
    {
        int x1 = character->GetActorLocation().X / 50;
        int y1 = character->GetActorLocation().Y / 50;

        int x22 = x1;
        int y22 = y1;

        TArray<AActor*> circuit = character->CurrentCircuit;
        FVector spawnpos = character->GetActorLocation();
        AActor* startCheckpoint = nullptr;
        if (circuit.Num() > 1)
        {
            x1 = circuit[circuit.Num()-1]->GetActorLocation().X / 50;
            y1 = circuit[circuit.Num() - 1]->GetActorLocation().Y / 50;
            spawnpos = circuit[circuit.Num() - 1]->GetActorLocation();

            if (character->Strategy == PathingStrategy::CIRCUIT)
            {
                startCheckpoint = circuit[circuit.Num() - 1];
                x22 = startCheckpoint->GetActorLocation().X / 50;
                y22 = startCheckpoint->GetActorLocation().Y / 50;

                AActor * currentCP = character->CurrentCircuit[character->CurrentCircuit.Num() - 1];
                int i = 0;

                while(((currentCP->GetActorLocation().X-25) /50 != x1 && (currentCP->GetActorLocation().Y-25) / 50 != y1))
                {
                    GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%f/%f"), (currentCP->GetActorLocation().X-25) / 50, (currentCP->GetActorLocation().Y-25) / 50));
                    character->CurrentCircuit[character->CurrentCircuit.Num() - 1]->Destroy();
                    character->CurrentCircuit.Pop();
                    currentCP = character->CurrentCircuit[character->CurrentCircuit.Num() - 1];    
                }
            }
        }

        int x2 = location.X/50;
        int y2 = location.Y/50;

        int heuristique = terrain->Manhattan(x1, y1, x2, y2);

        Noeud depart = {x1,y1,0,heuristique};
        Noeud objectif = {x2,y2,0,0};
        TArray<int> path = terrain->PathFinding(depart, objectif);

        
        for (int i = path.Num()-1 ; i >= 0; i--) {
            spawnpos = character->AddCheckPoint(path[i], spawnpos);
        }
        if (character->Strategy == PathingStrategy::CIRCUIT)
        {

            circuit = character->CurrentCircuit;
            x1 = circuit[circuit.Num()-1]->GetActorLocation().X /50;
            y1 = circuit[circuit.Num()-1]->GetActorLocation().Y/50;

            Noeud returnDepart = { x1,y1,0,heuristique };
            Noeud returnObjectif = { x22,y22,0,0 };        
           
            spawnpos = circuit[circuit.Num() - 1]->GetActorLocation();
            path = terrain->PathFinding(returnDepart, returnObjectif);
            pathToSpawn = path.Num();
            for (int i = path.Num() - 1; i >= 0; i--) {
                spawnpos = character->AddCheckPoint(path[i], spawnpos);
            }
        }
    }
}





