// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MainTreasure.h"
#include "Characters/Eve.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void AMainTreasure::OnPickup(AEve* Player)
{

	if (Player && WinWidget)
	{
		UUserWidget* WinScreen = CreateWidget<UUserWidget>(Player->GetWorld(), WinWidget);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
			if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
			Player->DisableInput(Cast<APlayerController>(Player->GetController()));
		}
		Destroy();
	}
}
