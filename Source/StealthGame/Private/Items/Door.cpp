#include "Items/Door.h"
#include "Characters/Eve.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

ADoor::ADoor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComponent);

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(150.f);
    InteractionSphere->SetCollisionProfileName("OverlapAllDynamic");

    bIsOpen = false;
    bIsOpening = false;
    OpenSpeed = 2.0f;
    OpenAngle = 90.f;
}

void ADoor::BeginPlay()
{
    Super::BeginPlay();

    ClosedRotation = DoorMesh->GetRelativeRotation();
    TargetRotation = ClosedRotation;
}

void ADoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsOpening)
    {
        FRotator Current = DoorMesh->GetRelativeRotation();
        FRotator NewRotation = FMath::RInterpConstantTo(Current, TargetRotation, DeltaTime, OpenSpeed * 50.f);
        DoorMesh->SetRelativeRotation(NewRotation);

        if (GEngine)
        {
            FString DebugText = FString::Printf(TEXT("Door Rotating: %.2f / %.2f"), NewRotation.Yaw, TargetRotation.Yaw);
            GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, DebugText);
        }

        if (FMath::Abs(NewRotation.Yaw - TargetRotation.Yaw) < 0.5f)
        {
            bIsOpening = false;
        }
    }
}

void ADoor::TryOpen(AEve* Player)
{
    if (Player && Player->bHasKey && !bIsOpen)
    {
        bIsOpen = true;
        bIsOpening = true;
        TargetRotation = ClosedRotation + FRotator(0.f, OpenAngle, 0.f);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Door Opening Triggered"));
        }
    }
}

bool ADoor::IsPlayerOverlapping(AEve* Player) const
{
    return InteractionSphere && Player && InteractionSphere->IsOverlappingActor(Player);
}
