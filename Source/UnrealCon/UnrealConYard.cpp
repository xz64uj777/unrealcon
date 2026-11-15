#include "UnrealConYard.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

AUnrealConYard::AUnrealConYard()
{
    PrimaryActorTick.bCanEverTick = false;
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("YardRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (!Cube.Succeeded()) return;

    auto AddBlock = [this, &Cube](const TCHAR* Name, FVector Location, FVector Scale)
    {
        UStaticMeshComponent* Block = CreateDefaultSubobject<UStaticMeshComponent>(Name);
        Block->SetupAttachment(GetRootComponent());
        Block->SetStaticMesh(Cube.Object);
        Block->SetRelativeLocation(Location);
        Block->SetRelativeScale3D(Scale);
        Block->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Block->SetMobility(EComponentMobility::Static);
    };

    AddBlock(TEXT("GroundSlab"), FVector(0, 0, -35), FVector(100, 100, 0.5f));
    AddBlock(TEXT("MainAccessRoad"), FVector(0, -1050, -5), FVector(100, 9, 0.08f));
    AddBlock(TEXT("Workshop"), FVector(-2200, 1900, 350), FVector(12, 9, 7));
    AddBlock(TEXT("PartsStore"), FVector(2100, 1900, 220), FVector(9, 8, 4.4f));
    AddBlock(TEXT("MaterialBayA"), FVector(-1900, -500, 180), FVector(8, 6, 3.6f));
    AddBlock(TEXT("MaterialBayB"), FVector(-1900, 500, 180), FVector(8, 6, 3.6f));
    AddBlock(TEXT("AggregatePileOne"), FVector(1450, -900, 90), FVector(5, 4, 1.8f));
    AddBlock(TEXT("AggregatePileTwo"), FVector(2100, -900, 75), FVector(4, 4, 1.5f));
    AddBlock(TEXT("EquipmentPad"), FVector(0, 1900, 12), FVector(34, 8, 0.24f));
}
