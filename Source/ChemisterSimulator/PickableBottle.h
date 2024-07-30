// Created by SULPIE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableObject.h"
#include "PickableBottle.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBottleBeginOverlap, APickableBottle*, AActor*);

UCLASS()
class CHEMISTERSIMULATOR_API APickableBottle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableBottle();
	void SetName(FString name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FOnBottleBeginOverlap OnBottleBeginOverlap;

	FString BottleName;

private:
	UStaticMeshComponent* bottleMesh;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
