#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnrealConVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class UNREALCON_API AUnrealConVehiclePawn : public APawn
{
    GENERATED_BODY()

public:
    AUnrealConVehiclePawn();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void Turn(float Value);

    UPROPERTY(VisibleAnywhere, Category="Vehicle")
    TObjectPtr<UStaticMeshComponent> VehicleBody;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(EditAnywhere, Category="Vehicle|Handling")
    float DriveSpeed = 900.0f;

    UPROPERTY(EditAnywhere, Category="Vehicle|Handling")
    float TurnRate = 75.0f;
};
