#include "UnrealConVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

AUnrealConVehiclePawn::AUnrealConVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = false;

    VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
    SetRootComponent(VehicleBody);
    VehicleBody->SetSimulatePhysics(false);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(VehicleBody);
    CameraBoom->TargetArmLength = 650.0f;
    CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 140.0f));
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 8.0f;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AUnrealConVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AUnrealConVehiclePawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AUnrealConVehiclePawn::Turn);
}

void AUnrealConVehiclePawn::MoveForward(float Value)
{
    if (FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        AddActorWorldOffset(GetActorForwardVector() * Value * DriveSpeed * GetWorld()->GetDeltaSeconds(), true);
    }
}

void AUnrealConVehiclePawn::Turn(float Value)
{
    if (FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        AddActorWorldRotation(FRotator(0.0f, Value * TurnRate * GetWorld()->GetDeltaSeconds(), 0.0f));
    }
}
