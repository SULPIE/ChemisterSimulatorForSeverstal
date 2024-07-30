// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementCreator.h"

// Sets default values
AElementCreator::AElementCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ELementCreatorMesh"));
	meshComponent->SetupAttachment(RootComponent);

	RootComponent = meshComponent;

	this->SetActorRotation(FRotator(0, 0, 90));
	this->SetActorScale3D(FVector(30.0f, 30.0f, 30.0f));
}

// Called when the game starts or when spawned
void AElementCreator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AElementCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

