// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "vector"
#include "iostream"

/**
 * 
 */
class CHEMISTERSIMULATOR_API PickableActorsCollector
{
public:
	PickableActorsCollector();
	~PickableActorsCollector();

	static void AddActorToVec(AActor* actor);
	static bool IsActorExist(AActor* actor);

private:
	static std::vector<AActor*> ActorsVector;
};