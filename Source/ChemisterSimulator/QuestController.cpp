// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestController.h"
#include "PlayerPawn.h"
#include "SynthesElementWidget.h"
#include "Barrels.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

QuestController* QuestController::Instance = nullptr;
std::unique_ptr<SpawnObjectController> QuestController::spawnBottleController;

FOnStartSynthesElement QuestController::OnStartSynthesElement;
FOnStopSynthesElement QuestController::OnStopSynthesElement;
FOnChangedQuestStage QuestController::OnChangedQuestStage;
FOnQuestControllerInit QuestController::OnQuestControllerInit;
FShowAllert QuestController::CallAllert;

std::vector<FString> QuestController::Stages = { TEXT("Подойдите к зеленой капсуле и нажмите на неё"), TEXT("Отнесите и вылейте колбу в фиолетовые бочки") };
std::vector<FString> QuestController::Elements = { "H2", "Na", "Li", "O", "Mg", "S", "O4", "K", "C", "Cr", "Rb", "Sr", "Zn", "Cd", "Te", "Pr", "Pm", "H", "F", "P" };
std::vector<APickableBottle*> QuestController::Bottles;
std::vector<int> QuestController::currElements;
std::vector<int> QuestController::IdxOfElements;

FString QuestController::SynthesText = "Синтузируйте ";

int QuestController::CurrentStage = 0;

QuestController::QuestController()
{
    Instance = this;

    ViewRayCastController* viewRayCastController = ViewRayCastController::GetViewRayCastControllerInstance();

    viewRayCastController->OnTouchAnyObject.AddRaw(this, &QuestController::OnTouchObject);

    StartQuest();
    ChangeStage(0);
}

QuestController::~QuestController() { }

QuestController* QuestController::GetInstance() { return Instance; }

void QuestController::StartQuest()
{
    currElements.clear();
    SynthesText = TEXT("Синтезируйте ");
    CurrentStage = 0;

    RandomizeFormula();
}

void QuestController::FinishQuest()
{
    StartQuest();
    OnChangedQuestStage.Broadcast(SynthesText, Stages[0]);
}

void QuestController::ChangeStage(int stage)
{
    OnChangedQuestStage.Broadcast(SynthesText, Stages[stage]);
}

void QuestController::SpawnBottle(FString elementName)
{
    for (auto start = Elements.begin(); start != Elements.end(); start++)
    {
        if (elementName == *start)
        {
            spawnBottleController = std::make_unique<SpawnObjectController>();
            APickableBottle* createdBottle = spawnBottleController->SpawnBottle(elementName, APlayerPawn::GetPlayerWorld(), FVector(-270.0, -160.0, 60.0f), FRotator(0, 0, 0));
            Bottles.push_back(createdBottle);
            createdBottle->OnBottleBeginOverlap.AddStatic(&QuestController::BottleBeginOverlap);
        }
    }
}

void QuestController::RandomizeFormula()
{
    IdxOfElements.clear();
    for (int idx = 0; idx < 4; idx++)
    {
        IdxOfElements.push_back(FMath::RandRange(0, (Elements.size() - 1)));
        SynthesText += Elements[IdxOfElements[idx]];
    }
}

void QuestController::OnCloseSynthesWidget(FString element)
{
    SpawnBottle(element);
    OnStopSynthesElement.Broadcast();
    ChangeStage(1);
}

void QuestController::OnTouchObject(AActor* object)
{
    AElementCreator* elementCreator = Cast<AElementCreator>(object);
    if (elementCreator != nullptr)
    {
        OnStartSynthesElement.Broadcast();
    }
}

void QuestController::BottleBeginOverlap(APickableBottle* bottle, AActor* otherObject)
{
    ABarrels* barrels = Cast<ABarrels>(otherObject);
    if (barrels == nullptr) { return; }

    CallAllert.Broadcast(TEXT("Вы залили элемент в бочку!"));

    FString name = bottle->BottleName;
    int elementid = 0;

    bottle->Destroy();

    for (auto start = Elements.begin(); start != Elements.end(); start++)
    {
        if (name == *start)
        {
            currElements.push_back(std::distance(Elements.begin(), start));
            UE_LOG(LogTemp, Warning, TEXT("%s"), *Elements[currElements[0]]);
        }
    }

    if (currElements.size() == MaxValueOfFormula)
    {
        int counter = 0;
        for (int i = 0; i < MaxValueOfFormula; i++) {
            for (int j = 0; j < MaxValueOfFormula; j++)
            {
                if (IdxOfElements[i] == currElements[j])
                {
                    counter++;
                    break;
                }
            }
        }

        if (counter == MaxValueOfFormula) {
            CallAllert.Broadcast(TEXT("Вы синтезировали химический элемент!"));
        }
        else {

            barrels->Explode();
            CallAllert.Broadcast(TEXT("Что-то пошло не так!"));
        }

        FinishQuest();
        return;
    }
    ChangeStage(0);
}
