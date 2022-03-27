// Fill out your copyright notice in the Description page of Project Settings.


#include "StearingObject.h"

AStearingObject::AStearingObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AStearingObject::BeginPlay()
{
	Super::BeginPlay();
	position = GetActorLocation();
	velocity = { -50.f,-50.f,0 };
	orientation = GetActorRotation();

}

// Called every frame
void AStearingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (target != NULL)
	{
		FVector current_strategy;
		switch (Strategy) {
		case CIRCUIT:
			current_strategy = Circuit();
			break;
		case ONEWAY:
			current_strategy = OneWay();

		default:
			current_strategy = OneWay();
			break;
		}

		FVector steering_force = Truncate(current_strategy, max_force);
		FVector acceleration = steering_force / mass;
		velocity = Truncate(velocity + acceleration, max_speed);
		position = position + velocity;
		orientation = velocity.Rotation();
		SetActorLocation(FVector(position.X, position.Y, position.Z));
		SetActorRotation(orientation);
	}
	else if (CurrentCircuit.Num() > 0) target = CurrentCircuit[0];
}


FVector AStearingObject::Truncate(FVector v, const float& max)
{
	if (v.Size() > max)
	{
		return v.GetSafeNormal() * max;
	}
	return v;
}

FVector AStearingObject::Seek()
{
	if (target == NULL) return position;
	FVector direction = (target->GetActorLocation() - position).GetSafeNormal();
	return direction * max_speed - velocity;
}


FVector AStearingObject::Circuit()
{
	max_speed = 3;
	if (target != NULL)
	{
		if ((target->GetActorLocation() - position).Size() < 5) {
			if (CurrentCircuit.Num() > 1)
			{
				AActor* first = CurrentCircuit[0];
				for (int i = 1; i < CurrentCircuit.Num(); ++i)
				{
					CurrentCircuit[i - 1] = CurrentCircuit[i];
				}
				CurrentCircuit[CurrentCircuit.Num() - 1] = first;
				CurrentCircuit[CurrentCircuit.Num() - 1]->Destroy();
				AActor* cp = CurrentCircuit.Pop();
				target = CurrentCircuit[0];
			}
			else
			{
				CurrentCircuit[CurrentCircuit.Num() - 1]->Destroy();
				AActor* cp = CurrentCircuit.Pop();
				target = NULL;
				max_speed = 0;
			}
		}
	}
	return Seek();
}

FVector AStearingObject::OneWay()
{
	max_speed = 3;
	if (target != NULL)
	{
		if ((target->GetActorLocation() - position).Size() < 5) {
			if (CurrentCircuit.Num() > 1)
			{
				AActor* first = CurrentCircuit[0];
				for (int i = 1; i < CurrentCircuit.Num(); ++i)
				{
					CurrentCircuit[i - 1] = CurrentCircuit[i];
				}
				CurrentCircuit[CurrentCircuit.Num() - 1] = first;
				CurrentCircuit[CurrentCircuit.Num() - 1]->Destroy();
				AActor* cp = CurrentCircuit.Pop();
				target = CurrentCircuit[0];
			}
			else
			{
				CurrentCircuit[CurrentCircuit.Num() - 1]->Destroy();
				AActor* cp = CurrentCircuit.Pop();
				target = NULL;
				max_speed = 0;
			}
		}
	}
	return Seek();
}