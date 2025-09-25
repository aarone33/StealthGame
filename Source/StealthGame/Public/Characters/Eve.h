// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Eve.generated.h"

class UInputMappingContext;
class UInputAction;
class UUserWidget;

UCLASS()
class STEALTHGAME_API AEve : public ACharacter
{
    GENERATED_BODY()

public:
    AEve();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Jump();

    UPROPERTY(EditAnywhere, Category = "Items")
    bool bHasKey = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Health = 100.f;

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
        AController* EventInstigator, AActor* DamageCauser) override;

protected:
    virtual void BeginPlay() override;
    virtual void Landed(const FHitResult& Hit) override;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* EveContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MovementAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* EKeyPress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    UUserWidget* GameOverWidget;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void EKeyPressed();
};
