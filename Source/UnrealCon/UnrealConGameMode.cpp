#include "UnrealConGameMode.h"
#include "UnrealConVehiclePawn.h"
#include "UnrealConYard.h"
#include "Engine/World.h"

AUnrealConGameMode::AUnrealConGameMode()
{
    DefaultPawnClass = AUnrealConVehiclePawn::StaticClass();
}

void AUnrealConGameMode::BeginPlay()
{
    Super::BeginPlay();
    if (UWorld* World = GetWorld())
    {
        World->SpawnActor<AUnrealConYard>(AUnrealConYard::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    }
}
