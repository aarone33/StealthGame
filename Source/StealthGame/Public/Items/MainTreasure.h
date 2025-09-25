// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Items.h"
#include "MainTreasure.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AMainTreasure : public AItems
{
	GENERATED_BODY()
	
public:

	virtual void OnPickup(AEve* Player) override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> WinWidget;
};
