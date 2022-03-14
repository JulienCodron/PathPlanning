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

}

void ANPC_PlayerController::FollowPath(TArray<int> path)
{
    if (path.Num() < 0) return;
    
    character = Cast<Anpc>(this->GetCharacter());
    character->MoveForward(50);
    //FAIRE UN MOOVETO(location) //Moveforward, turnrate etccccc voir escape game
    //for (int direction : path)
    //{
    //    switch (direction)
    //    {
    //    case 0: //haut
    //        character->MoveForward(50.f);
    //        break;
    //    case 1: //droite
    //        character->MoveRight(50.f);
    //        break;
    //    case 2: //bas
    //        character->MoveForward(-50.f);
    //        break;
    //    case 3: //gauche
    //        character->MoveRight(-50.f);
    //        break;
    //    default:
    //        break;
    //    }
    //}
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
        path = { 0,0,0,1,1,1,0,0,2,2,3,3,3,2,2,2 };
        FollowPath(path);
    }
}





