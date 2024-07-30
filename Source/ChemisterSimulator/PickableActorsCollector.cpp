// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActorsCollector.h"

std::vector<AActor*> PickableActorsCollector::ActorsVector = {};

PickableActorsCollector::PickableActorsCollector()
{
}

PickableActorsCollector::~PickableActorsCollector()
{
}

void PickableActorsCollector::AddActorToVec(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Added"));
	ActorsVector.push_back(actor);
}

bool PickableActorsCollector::IsActorExist(AActor* actor)
{
	for (int i = 0; i < ActorsVector.size(); i++)
	{
		if (ActorsVector[i] == actor)
		{
			return true;
		}
	}
	return false;
}
