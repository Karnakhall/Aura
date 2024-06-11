// Copyright Karnakhall


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);	// Check if the context is valid

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);	// Check if the subsystem is valid
	Subsystem->AddMappingContext(AuraContext, 0);	// Add the context to the subsystem

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	// Don't lock the mouse in viewport
	InputModeData.SetHideCursorDuringCapture(false);	// Don't hide the cursor during capture
	SetInputMode(InputModeData);
}
