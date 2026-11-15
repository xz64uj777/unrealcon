#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealConGameMode.generated.h"

UCLASS()
class UNREALCON_API AUnrealConGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AUnrealConGameMode();
    virtual void BeginPlay() override;
};
