// Created by SULPIE


#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UWorld* APlayerPawn::PlayerWorld;

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitPawnSettings();
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerWorld = GetWorld();
	questController = std::make_unique<QuestController>();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	viewRayCastController->DetectAnActor(GetWorld(), GetActorForwardVector(), GetActorLocation());
	PlayerPickup();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("RotateY"), this, &APlayerPawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("RotateP"), this, &APlayerPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &APlayerPawn::OnPlayerMoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerPawn::OnPlayerMoveLeftRight);
}

UWorld* APlayerPawn::GetPlayerWorld()
{
	return PlayerWorld;
}

void APlayerPawn::OnPlayerMoveForwardBackward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value * 0.2);
}

void APlayerPawn::OnPlayerMoveLeftRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value * 0.2);
}

void APlayerPawn::InitPawnSettings()
{
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	PlayerCamera->SetupAttachment(RootComponent);
	bUseControllerRotationPitch = true;

	viewRayCastController = std::make_unique<ViewRayCastController>(this);
}

void APlayerPawn::PlayerPickup()
{
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		viewRayCastController->AttachSelectedActor();
		viewRayCastController->TouchedAnyObject();
		UE_LOG(LogTemp, Warning, TEXT("Interrupt"));
	}
}

