#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class AEve;
class USphereComponent;

UCLASS()
class STEALTHGAME_API ADoor : public AActor
{
    GENERATED_BODY()

public:
    ADoor();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Door")
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(VisibleAnywhere, Category = "Door")
    USphereComponent* InteractionSphere;

    bool bIsOpen = false;

public:
    void TryOpen(AEve* Player);

    UPROPERTY(EditAnywhere, Category = "Door")
    float OpenAngle = 90.f;

    UPROPERTY(EditAnywhere, Category = "Door")
    float OpenSpeed = 2.f;

    FRotator ClosedRotation;
    FRotator TargetRotation;
    bool bIsOpening = false;

    bool IsPlayerOverlapping(AEve* Player) const;
};
