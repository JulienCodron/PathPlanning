// Fill out your copyright notice in the Description page of Project Settings.


#include "npc.h"

// Sets default values
Anpc::Anpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called to bind functionality to input
void Anpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis("MoveForward", this, &ATarget::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATarget::MoveRight);*/
}

