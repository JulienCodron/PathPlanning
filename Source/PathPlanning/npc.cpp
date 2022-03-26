// Fill out your copyright notice in the Description page of Project Settings.


#include "npc.h"
#include "NPC_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <time.h>
#include <chrono>
#include <thread>

// Sets default values
Anpc::Anpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

}

// Called when the game starts or when spawned
void Anpc::BeginPlay()
{
	Super::BeginPlay();
	directionLocation = GetActorLocation();
}

// Called every frame
void Anpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (path.Num()>0 && GetActorLocation().Equals(directionLocation,10.f))
	{
		int direction = path[0];
		switch (direction)
		{
		case 0: //haut
			directionLocation = { GetActorLocation().X + 50 ,GetActorLocation().Y,GetActorLocation().Z };
			MoveForward(70.f);
			break;
		case 1: //droite
			directionLocation = { GetActorLocation().X ,GetActorLocation().Y + 50,GetActorLocation().Z };
			MoveRight(70.f);
			break;
		case 2: //bas
			directionLocation = { GetActorLocation().X - 50, GetActorLocation().Y, GetActorLocation().Z };
			MoveForward(-70.f);
			break;
		case 3: //gauche
			directionLocation = { GetActorLocation().X ,GetActorLocation().Y - 50 ,GetActorLocation().Z };
			MoveRight(-70.f);
			break;
		default:
			break;
		}
		if (path.Num() <= 1) {
			path = {};
		}
		else
		{
			for (int i = 1; i < path.Num(); i++)
				path[i - 1] = path[i];
			path.Pop();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%f/%f/%f"), directionLocation.X, directionLocation.Y, directionLocation.Z));
	}
}

void Anpc::MoveForward(float Value)
{
	clock_t start = clock();
	if ((Controller != nullptr) && (Value != 0.0f))
	{	
		FVector goal = {GetActorLocation().X + Value, GetActorLocation().Y , GetActorLocation().Z};
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), goal);
	}
}

void Anpc::MoveRight(float Value)
{
	clock_t start = clock();
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FVector goal = { GetActorLocation().X  , GetActorLocation().Y + Value, GetActorLocation().Z };
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(),goal);
	}
}

FVector Anpc::isntMoving()
{
	return GetActorLocation();
}

// Called to bind functionality to input
void Anpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
}

