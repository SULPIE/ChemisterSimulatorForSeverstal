// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "ViewRayCastController.h"
#include "QuestController.h"
#include "ChemisterHUDWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CHEMISTERSIMULATOR_API UChemisterHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Crosshair;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameOfSelectedItem;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MainTask;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SubTask;
	UPROPERTY(meta = (BindWidget))
	UBorder* AllertBorder;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Allert;

private:
	void OnSelectedObject(FString NameOfObject);
	void OnUntouchObject();

	FTimerHandle MyTimerHandle;

	void OnQuestStageChanged(FString stage, FString substage);
	void ShowAllert(FString message);
	void OnTimer();
};
