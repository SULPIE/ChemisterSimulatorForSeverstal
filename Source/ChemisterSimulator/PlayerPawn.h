// Created by SULPIE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "ViewRayCastController.h"
#include "iostream"
#include "functional"
#include "QuestController.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CHEMISTERSIMULATOR_API APlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	static UWorld* GetPlayerWorld();

private:

	void OnPlayerMoveForwardBackward(float Value);
	void OnPlayerMoveLeftRight(float Value);

	void InitPawnSettings();

	//Default player's camera
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	UMeshComponent* PlayerMesh;

	std::unique_ptr<QuestController> questController;
	std::unique_ptr<ViewRayCastController> viewRayCastController;

	void PlayerPickup();

	static UWorld* PlayerWorld;
};
