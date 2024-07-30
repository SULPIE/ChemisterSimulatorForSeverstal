// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerPawn.h"
#include "ChemisterHUD.h"
#include "ChemisterSimulatorGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHEMISTERSIMULATOR_API AChemisterSimulatorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;
private:
	void InitPlayerInstances();
};
