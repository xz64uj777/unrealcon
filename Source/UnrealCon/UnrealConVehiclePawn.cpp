#include "UnrealConVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"

AUnrealConVehiclePawn::AUnrealConVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
    SetRootComponent(VehicleBody);
    VehicleBody->SetStaticMesh(CubeMesh.Object);
    VehicleBody->SetRelativeScale3D(FVector(2.4f, 1.25f, 0.42f));
    VehicleBody->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));
    VehicleBody->SetSimulatePhysics(false);

    UStaticMesh* Cube = CubeMesh.Object;
    auto AddPart = [this, Cube](const TCHAR* Name, const FVector& Location, const FVector& Scale)
    {
        UStaticMeshComponent* Part = CreateDefaultSubobject<UStaticMeshComponent>(Name);
        Part->SetupAttachment(VehicleBody);
        Part->SetStaticMesh(Cube);
        Part->SetRelativeLocation(Location);
        Part->SetRelativeScale3D(Scale);
        Part->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        return Part;
    };

    AddPart(TEXT("LoaderCab"), FVector(-35.0f, 0.0f, 100.0f), FVector(0.72f, 0.88f, 0.92f));
    AddPart(TEXT("LoaderRear"), FVector(-105.0f, 0.0f, 80.0f), FVector(0.72f, 1.0f, 0.48f));
    AddPart(TEXT("LoaderFront"), FVector(95.0f, 0.0f, 83.0f), FVector(0.75f, 1.0f, 0.50f));
    AddPart(TEXT("LiftArmLeft"), FVector(115.0f, -52.0f, 122.0f), FVector(1.05f, 0.13f, 0.13f));
    AddPart(TEXT("LiftArmRight"), FVector(115.0f, 52.0f, 122.0f), FVector(1.05f, 0.13f, 0.13f));
    AddPart(TEXT("Bucket"), FVector(205.0f, 0.0f, 65.0f), FVector(0.48f, 0.82f, 0.16f));

    if (CylinderMesh.Succeeded())
    {
        for (int32 X : {-1, 1})
        {
            for (int32 Y : {-1, 1})
            {
                UStaticMeshComponent* Wheel = CreateDefaultSubobject<UStaticMeshComponent>(
                    *FString::Printf(TEXT("Wheel_%d_%d"), X, Y));
                Wheel->SetupAttachment(VehicleBody);
                Wheel->SetStaticMesh(CylinderMesh.Object);
                Wheel->SetRelativeLocation(FVector(X * 125.0f, Y * 75.0f, 43.0f));
                Wheel->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
                Wheel->SetRelativeScale3D(FVector(0.48f, 0.22f, 0.48f));
                Wheel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }
        }
    }

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(VehicleBody);
    CameraBoom->TargetArmLength = 850.0f;
    CameraBoom->SetRelativeLocation(FVector(-80.0f, 0.0f, 220.0f));
    CameraBoom->SetRelativeRotation(FRotator(-12.0f, 0.0f, 0.0f));
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
    PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &AUnrealConVehiclePawn::CameraYaw);
    PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &AUnrealConVehiclePawn::CameraPitch);
}

void AUnrealConVehiclePawn::MoveForward(float Value)
{
    if (FMath::Abs(Value) > KINDA_SMALL_NUMBER && GetWorld())
    {
        AddActorWorldOffset(GetActorForwardVector() * Value * DriveSpeed * GetWorld()->GetDeltaSeconds(), true);
    }
}

void AUnrealConVehiclePawn::Turn(float Value)
{
    if (FMath::Abs(Value) > KINDA_SMALL_NUMBER && GetWorld())
    {
        AddActorWorldRotation(FRotator(0.0f, Value * TurnRate * GetWorld()->GetDeltaSeconds(), 0.0f));
    }
}

void AUnrealConVehiclePawn::CameraYaw(float Value)
{
    AddControllerYawInput(Value);
}

void AUnrealConVehiclePawn::CameraPitch(float Value)
{
    AddControllerPitchInput(Value);
}
