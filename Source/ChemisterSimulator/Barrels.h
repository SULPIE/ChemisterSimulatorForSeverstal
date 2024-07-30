// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrels.generated.h"

UCLASS()
class CHEMISTERSIMULATOR_API ABarrels : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrels();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	USoundBase* soundExplosion;

	void Explode();
};
