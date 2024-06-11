// Copyright Karnakhall


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);	// We check if the input component is valid if not we crash

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxistVector = InputActionValue.Get<FVector2D>();	// Get the input value
	const FRotator Rotation = GetControlRotation();	// Get the control rotation
	const FRotator YawRotation(0, Rotation.Yaw, 0);	// Get the yaw rotation

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	// Get the forward direction
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);	// Get the right direction

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxistVector.Y);	// Add the forward movement
		ControlledPawn->AddMovementInput(RightDirection, InputAxistVector.X);		// Add the right movement
	}
}
