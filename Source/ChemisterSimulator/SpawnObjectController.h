// Created by SULPIE

#pragma once

#include "CoreMinimal.h"
#include "PickableActorsCollector.h"
#include "PickableBottle.h"

/**
 * 
 */
class CHEMISTERSIMULATOR_API SpawnObjectController
{
public:
	SpawnObjectController(const SpawnObjectController&) = delete;
	SpawnObjectController(SpawnObjectController&&) = delete;
	SpawnObjectController& operator = (const SpawnObjectController&) = delete;
	SpawnObjectController& operator = (SpawnObjectController&&) = delete;

	SpawnObjectController();
	~SpawnObjectController();

	APickableBottle* SpawnBottle(FString name, UWorld* world, FVector location, FRotator rotation);

private:
	APickableBottle* createdBottle;
};
