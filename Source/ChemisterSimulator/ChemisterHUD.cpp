// Fill out your copyright notice in the Description page of Project Settings.


#include "ChemisterHUD.h"

AChemisterHUD::~AChemisterHUD() {
}

void AChemisterHUD::BeginPlay()
{
	Super::BeginPlay();

	synthesElementWidget = CreateWidget<USynthesElementWidget>(GetOwningPlayerController(), SynthesisPotionWidget);
	chemisterHudWidget = CreateWidget<UChemisterHUDWidget>(GetOwningPlayerController(), CrosshairWidget);
	chemisterHudWidget->AddToViewport();

	QuestController::OnStartSynthesElement.AddUObject(this, &AChemisterHUD::OnStartSynthes);
	QuestController::OnStopSynthesElement.AddUObject(this, &AChemisterHUD::OnStopSynthes);

	chemisterHudWidget->AddToRoot();
	synthesElementWidget->AddToRoot();
}

void AChemisterHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	chemisterHudWidget->RemoveFromRoot();
	synthesElementWidget->RemoveFromRoot();
}

void AChemisterHUD::OnStartSynthes()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(synthesElementWidget->GetName()));
	if (!synthesElementWidget->IsInViewport())
	{
		chemisterHudWidget->RemoveFromViewport();
		synthesElementWidget->AddToViewport();
	}
}

void AChemisterHUD::OnStopSynthes()
{
	if (!chemisterHudWidget->IsInViewport())
	{
		synthesElementWidget->RemoveFromViewport();
		chemisterHudWidget->AddToViewport();
	}
}
