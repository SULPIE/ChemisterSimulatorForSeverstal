// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "iostream"
#include "vector"
#include "PickableBottle.h"
#include "SpawnObjectController.h"
#include "ViewRayCastController.h"
#include "ElementCreator.h"

DECLARE_MULTICAST_DELEGATE(FOnQuestControllerInit);
DECLARE_MULTICAST_DELEGATE(FOnStartSynthesElement);
DECLARE_MULTICAST_DELEGATE(FOnStopSynthesElement);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedQuestStage, FString, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FShowAllert, FString);

class USynthesElementWidget;
class APlayerPawn;
class CHEMISTERSIMULATOR_API QuestController
{
public:
	QuestController();
	~QuestController();

	QuestController(const QuestController&) = delete;
	QuestController(QuestController&&) = delete;
	QuestController& operator = (const QuestController&) = delete;
	QuestController& operator = (QuestController&&) = delete;

	static QuestController* GetInstance();

	static FOnStartSynthesElement OnStartSynthesElement;
	static FOnStopSynthesElement OnStopSynthesElement;
	static FOnQuestControllerInit OnQuestControllerInit;
	static FOnChangedQuestStage OnChangedQuestStage; 
	static FShowAllert CallAllert;

	static void OnCloseSynthesWidget(FString element);
	static std::unique_ptr<SpawnObjectController> spawnBottleController;

private:
	static QuestController* Instance;

	static std::vector<FString> Stages;
	static std::vector<FString> Elements;
	static std::vector<int> currElements;
	static FString SynthesText;

	static std::vector<int> IdxOfElements;

	static int CurrentStage;
	std::string CurrentFormula;
	static const int MaxValueOfFormula = 4;

	static std::vector<APickableBottle*> Bottles;

	static void StartQuest();
	static void FinishQuest();
	static void ChangeStage(int stage);

	static void SpawnBottle(FString elementName);
	static void RandomizeFormula();

	void OnTouchObject(AActor* object);
	static void BottleBeginOverlap(APickableBottle* bottle, AActor* otherObject);
};
