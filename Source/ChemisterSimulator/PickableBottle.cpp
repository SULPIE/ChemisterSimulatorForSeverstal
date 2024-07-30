// Created by SULPIE


#include "PickableBottle.h"

// Sets default values
APickableBottle::APickableBottle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	bottleMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("StaticMesh'/Game/Meshes/erlenmayer_turbosquid.erlenmayer_turbosquid'"));
	bottleMesh->SetStaticMesh(CylinderAsset.Object);

	RootComponent = bottleMesh;
	
	this->SetActorRotation(FRotator(0, 0, 90));
	this->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));

	bottleMesh->SetSimulatePhysics(true);
}

void APickableBottle::SetName(FString name)
{
	BottleName = name;
}

// Called when the game starts or when spawned
void APickableBottle::BeginPlay()
{
	Super::BeginPlay();

	bottleMesh->SetGenerateOverlapEvents(true);
	bottleMesh->OnComponentBeginOverlap.AddDynamic(this, &APickableBottle::BeginOverlap);
}

// Called every frame
void APickableBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableBottle::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnBottleBeginOverlap.Broadcast(this, OtherActor);
}

