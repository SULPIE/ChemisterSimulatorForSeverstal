// Created by SULPIE

#include "ViewRayCastController.h"
#include "PickableBottle.h"

ViewRayCastController* ViewRayCastController::viewRayCastControllerInstance = nullptr;

ViewRayCastController::ViewRayCastController(const APawn* _PlayerPawn) : PlayerPawn(_PlayerPawn) { viewRayCastControllerInstance = this; }

ViewRayCastController::~ViewRayCastController() { }

void ViewRayCastController::DetectAnActor(const UWorld* world, const FVector actorForwardVector, const FVector actorLocation)
{
	if (world == nullptr) { return; }

	const auto Start = actorLocation - actorForwardVector * startRayMultiplier;
	const auto End = actorLocation + actorForwardVector * endRayMultiplier;

	FHitResult HitResult;
	FCollisionQueryParams COQP;
	FCollisionResponseParams CollRes;

	if (world->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, COQP, CollRes)) 
	{
		if (HitResult.bBlockingHit)
		{
			if (isActorVisible == true && HitResult.Actor == currActor) { return; }
			isActorVisible = true;

			currActor = HitResult.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(HitResult.GetActor()->GetName()));
			TouchedSelectedActor();
		}
	}
	else
	{
		if (isActorVisible)
		{
			currActor = nullptr;
			isActorVisible = !isActorVisible;
			UntouchedSelectedActor();
		}
	}
}

void ViewRayCastController::AttachSelectedActor()
{
	if (currActor == nullptr) { return; }

	if (!PickableActorsCollector::IsActorExist(currActor)) { return; }

	USceneComponent* PlayerMesh = PlayerPawn->GetRootComponent();
	UStaticMeshComponent* SkeletalMesh = currActor->FindComponentByClass<UStaticMeshComponent>();

	if (!isActorAttached)
	{
		currActor->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::KeepWorld, 
			EAttachmentRule::KeepWorld, 
			EAttachmentRule::KeepWorld, true));
		UE_LOG(LogTemp, Warning, TEXT("Attached"));
	}
	else
	{
		currActor->DetachAllSceneComponents(PlayerMesh, FDetachmentTransformRules(EDetachmentRule::KeepWorld, 
			EDetachmentRule::KeepWorld, 
			EDetachmentRule::KeepWorld, true));
		currActor = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Detached"));
	}

	SkeletalMesh->SetSimulatePhysics(isActorAttached);
	isActorAttached = !isActorAttached;
}

void ViewRayCastController::TouchedSelectedActor()
{
	APickableBottle* bottle = Cast<APickableBottle>(currActor);
	if (bottle == nullptr) { return; }

	if (currActor == nullptr) { return; }
	if (!PickableActorsCollector::IsActorExist(currActor)) { return; }

	OnSelectedObject.Broadcast(bottle->BottleName);
}

void ViewRayCastController::UntouchedSelectedActor()
{
	OnPutAwayObject.Broadcast();
}

void ViewRayCastController::TouchedAnyObject()
{
	if (currActor == nullptr) { return; }

	OnTouchAnyObject.Broadcast(currActor);
}

ViewRayCastController* ViewRayCastController::GetViewRayCastControllerInstance()
{
	return viewRayCastControllerInstance;
}
