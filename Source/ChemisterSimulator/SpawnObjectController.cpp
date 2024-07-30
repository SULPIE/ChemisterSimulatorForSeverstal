// Created by SULPIE


#include "SpawnObjectController.h"

SpawnObjectController::SpawnObjectController() { }

SpawnObjectController::~SpawnObjectController() { }

APickableBottle* SpawnObjectController::SpawnBottle(FString name, UWorld* world, FVector location, FRotator rotation)
{
	FActorSpawnParameters SpawnInfo;
	createdBottle = world->SpawnActor<APickableBottle>(location, rotation, SpawnInfo);
	PickableActorsCollector::AddActorToVec(createdBottle);
	createdBottle->SetName(name);
	return createdBottle;
}
