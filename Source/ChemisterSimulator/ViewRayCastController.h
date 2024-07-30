// Created by SULPIE

#pragma once

#include "CoreMinimal.h"
#include "iostream"
#include "functional"
#include "PickableObject.h"
#include "PickableActorsCollector.h"
#include "Runtime/Engine/Classes/Engine/World.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedObject, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTouchAnyObject, AActor*);
DECLARE_MULTICAST_DELEGATE(FOnPutAwayObject);

class CHEMISTERSIMULATOR_API ViewRayCastController final
{
public:
	ViewRayCastController(const APawn* _PlayerPawn);
	~ViewRayCastController();

	ViewRayCastController(const ViewRayCastController&) = delete;
	ViewRayCastController(ViewRayCastController&&) = delete;
	ViewRayCastController& operator = (const ViewRayCastController&) = delete;
	ViewRayCastController& operator = (ViewRayCastController&&) = delete;

	FOnSelectedObject OnSelectedObject;
	FOnPutAwayObject OnPutAwayObject;

	FOnTouchAnyObject OnTouchAnyObject;

	void DetectAnActor(const UWorld* world, const FVector actorForwardVector, const FVector actorLocation);
	void AttachSelectedActor();
	void TouchedSelectedActor();
	void UntouchedSelectedActor();

	void TouchedAnyObject();

	static ViewRayCastController* GetViewRayCastControllerInstance();

private:
	const float startRayMultiplier = 200.0f;
	const float endRayMultiplier = 150.0f;

	const APawn* PlayerPawn;

	AActor* currActor = nullptr;
	bool isActorAttached = false;
	bool isActorVisible = false;

	static ViewRayCastController* viewRayCastControllerInstance;
};
