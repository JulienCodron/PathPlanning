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

void ANPC_PlayerController::OnMouseClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
    FVector location = HitResult.Location;
    character = Cast<Anpc>(this->GetCharacter());

    if (HitResult.GetComponent() && character!=NULL)
    {
        int x1 = character->GetActorLocation().X / 50;
        int y1 = character->GetActorLocation().Y / 50;

        int x2 = location.X/50;
        int y2 = location.Y/50;

        int heuristique = terrain->Manhattan(x1, y1, x2, y2);

        Noeud depart = {x1,y1,0,heuristique};
        Noeud objectif = {x2,y2,0,0};
        TArray<int> path = terrain->PathFinding(depart, objectif);
        for (int i = path.Num()-1 ; i >= 0; i--) {
            character->path.Add(path[i]);
        }
    }
}





