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

    character = Cast<Anpc>(this->GetCharacter());
    if (!character) { GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "No Character Found (NPC_PlayerController)"); }
    else { GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, character->GetName()); }
}

void ANPC_PlayerController::OnMouseClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
    FVector location = HitResult.Location;

    if (HitResult.GetComponent())
    {
        int PosXOnMatrix = 20 - location.X/50;
        int PosYOnMatrix = location.Y/50;

        TArray<int> path = terrain->PathFinding(PosXOnMatrix, PosYOnMatrix);
        FollowPath(path);
    }
}


void ANPC_PlayerController::FollowPath(TArray<int> path)
{
    if (path.Num() < 0) return;

    //FAIRE UN MOOVETO(location) //Moveforward, turnrate etccccc voir escape game
    for (int direction : path)
    {
        switch (direction)
        {
        case 0: //haut
            break;
        case 1: //droite
            break;
        case 2: //bas
            break;
        case 3: //gauche
            break;
        default:
            break;
        }
    }
}



