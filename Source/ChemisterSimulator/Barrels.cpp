// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrels.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABarrels::ABarrels()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelsMesh"));
	soundExplosion = CreateDefaultSubobject<USoundBase>(TEXT("SoundExplosion"));
	meshComponent->SetupAttachment(RootComponent);

	RootComponent = meshComponent;

	meshComponent->bUseDefaultCollision = true;

	this->SetActorRotation(FRotator(0, 0, 90));
	this->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
}

// Called when the game starts or when spawned
void ABarrels::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABarrels::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrels::Explode()
{
	UGameplayStatics::PlaySound2D(GetWorld(), soundExplosion, 0.7, 1, 0);
}

