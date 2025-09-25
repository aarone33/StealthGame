// Copyright Epic Games, Inc. All Rights Reserved.


#include "StealthGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "StealthGameCameraManager.h"

AStealthGamePlayerController::AStealthGamePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AStealthGameCameraManager::StaticClass();
}

void AStealthGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
