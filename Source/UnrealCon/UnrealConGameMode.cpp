#include "UnrealConGameMode.h"
#include "UnrealConVehiclePawn.h"

AUnrealConGameMode::AUnrealConGameMode()
{
    DefaultPawnClass = AUnrealConVehiclePawn::StaticClass();
}
