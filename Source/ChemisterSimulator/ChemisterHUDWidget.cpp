// Fill out your copyright notice in the Description page of Project Settings.


#include "ChemisterHUDWidget.h"

void UChemisterHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ViewRayCastController* viewRayCastController = ViewRayCastController::GetViewRayCastControllerInstance();
	viewRayCastController->OnSelectedObject.AddUObject(this, &UChemisterHUDWidget::OnSelectedObject);
	viewRayCastController->OnPutAwayObject.AddUObject(this, &UChemisterHUDWidget::OnUntouchObject);

	QuestController* questController = QuestController::GetInstance();
	questController->OnChangedQuestStage.AddUObject(this, &UChemisterHUDWidget::OnQuestStageChanged);
	questController->CallAllert.AddUObject(this, &UChemisterHUDWidget::ShowAllert);
}

void UChemisterHUDWidget::OnSelectedObject(FString NameOfObject)
{
	NameOfSelectedItem->SetText(FText::FromString(NameOfObject));
}

void UChemisterHUDWidget::OnUntouchObject()
{
	NameOfSelectedItem->SetText(FText::FromString(""));
}

void UChemisterHUDWidget::OnQuestStageChanged(FString stage, FString substage)
{
	MainTask->SetText(FText::FromString(stage));
	SubTask->SetText(FText::FromString(substage));
}

void UChemisterHUDWidget::ShowAllert(FString message)
{
	AllertBorder->SetVisibility(ESlateVisibility::Visible);
	Allert->SetText(FText::FromString(message));

	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UChemisterHUDWidget::OnTimer, 3.0f, false);
}

void UChemisterHUDWidget::OnTimer()
{
	AllertBorder->SetVisibility(ESlateVisibility::Hidden);
	Allert->SetText(FText::FromString(""));
}
