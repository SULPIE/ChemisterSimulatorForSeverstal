// Fill out your copyright notice in the Description page of Project Settings.


#include "SynthesElementWidget.h"

FOnCloseSynthesWidget USynthesElementWidget::OnCloseSynthesWidget;

void USynthesElementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AddPlayerMouseControl(true);
	FormulaCreate->OnClicked.AddUniqueDynamic(this, &USynthesElementWidget::OnFormulaCreateButtonClick);
}

void USynthesElementWidget::OnFormulaCreateButtonClick()
{
	if (FormulaInput->GetText().ToString() != "") {
		AddPlayerMouseControl(false);
		//OnCloseSynthesWidget.Broadcast(FormulaInput->GetText().ToString());
		QuestController::OnCloseSynthesWidget(FormulaInput->GetText().ToString());
	}
}

void USynthesElementWidget::AddPlayerMouseControl(bool enable)
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = enable;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = enable;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = enable;

	if (enable)
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
}
