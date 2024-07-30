// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChemisterSimulatorGameModeBase.h"

void AChemisterSimulatorGameModeBase::InitGameState()
{
	Super::InitGameState();

	InitPlayerInstances();
}

void AChemisterSimulatorGameModeBase::InitPlayerInstances()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
}
