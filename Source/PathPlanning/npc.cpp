// Fill out your copyright notice in the Description page of Project Settings.


#include "npc.h"
#include "NPC_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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
	
}

// Called every frame
void Anpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Anpc::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		bool arriver = false;

		FVector Direction = { 0,90,0 };
		if (Value < 0.0f)
		{
			Direction = { 0,0, 240 };
		}
		AddActorWorldRotation(Direction.ToOrientationQuat());

		FVector goal = {GetActorLocation().X + Value, GetActorLocation().Y , GetActorLocation().Z};
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), goal);

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, 0, false);
		/*while (!arriver || GetWorld()->GetTimerManager().GetTimerElapsed(timer) > 1.0f) {
			if (GetActorLocation().Equals(goal, 5)) arriver = true;
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("%f"), GetWorld()->GetTimerManager().GetTimerElapsed(timer)));
		}
		GetWorld()->GetTimerManager().ClearTimer(timer);*/
	}
}

void Anpc::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		bool arriver = false;
		FVector Direction = { 0,0,0 };
		if (Value < 0.0f) 
		{
			Direction = { 0,0,180 };
		}
		SetActorRotation(Direction.ToOrientationQuat());

		FVector goal = { GetActorLocation().X  , GetActorLocation().Y + Value, GetActorLocation().Z };
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), goal);

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer,0,false);
		/*while (!arriver || GetWorld()->GetTimerManager().GetTimerElapsed(timer) > 1.0f) {
			if (GetActorLocation().Equals(goal, 5)) arriver = true;
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT( "%f"), GetWorld()->GetTimerManager().GetTimerElapsed(timer)));
		}
		GetWorld()->GetTimerManager().ClearTimer(timer);*/
	}
}


// Called to bind functionality to input
void Anpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
}

