// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "SynthesElementWidget.h"
#include "ChemisterHUDWidget.h"
#include "QuestController.h"
#include "ChemisterHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CHEMISTERSIMULATOR_API AChemisterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	~AChemisterHUD();

private:
	UChemisterHUDWidget* chemisterHudWidget;
	USynthesElementWidget* synthesElementWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CrosshairWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SynthesisPotionWidget;

	void OnStartSynthes();
	void OnStopSynthes();
};
