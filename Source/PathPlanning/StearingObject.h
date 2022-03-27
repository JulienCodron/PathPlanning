// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StearingObject.generated.h"

UENUM()
enum PathingStrategy {
	CIRCUIT UMETA(DisplayName = "Circuit"),
	ONEWAY UMETA(DisplayName = "OneWay"),
};


UCLASS()
class PATHPLANNING_API AStearingObject : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		float mass = 10.f;

	FVector position;
	FVector velocity;
	FRotator orientation;
	int circuitIndex = 0;

	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		float max_force = 1.f;

	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		float max_speed = 10.f;

	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		AActor* target;

	bool WayEnd = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> CurrentCircuit;

	UPROPERTY(EditAnywhere, Category = "StearingParam", meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<PathingStrategy> Strategy;

	AStearingObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector Truncate(FVector v, const float& max);
	FVector Seek();
	FVector Circuit();
	FVector OneWay();
};