// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "QuestController.h"
#include "SynthesElementWidget.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCloseSynthesWidget, FString);

UCLASS(Abstract)
class CHEMISTERSIMULATOR_API USynthesElementWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	static FOnCloseSynthesWidget OnCloseSynthesWidget;

protected:
	UPROPERTY(meta = (BindWidget))
	UEditableText* FormulaInput;
	UPROPERTY(meta = (BindWidget))
	UButton* FormulaCreate;

	UFUNCTION()
	void OnFormulaCreateButtonClick();

protected:
	void AddPlayerMouseControl(bool enable);
};
