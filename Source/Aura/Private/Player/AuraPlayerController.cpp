// Copyright Karnakhall


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/*
	* Line trace from cursor. There are several scenarios:
	* A. LastActor is null && ThisActor is null
	*	 - Do nothing
	* B. LastActor is null && ThisActor is valid
	*	 - Call HighLightActor on ThisActor
	* C. LastActor is valid && ThisActor is null
	*	 - Call UnHighLightActor on LastActor
	* D. LastActor is valid && ThisActor is valid, but LastActor != ThisActor
	*	 - Call UnHighLightActor on LastActor, and HighLightActor on ThisActor
	* E. Both LastActor and ThisActor are valid, and LastActor == ThisActor
	*	 - Do nothing
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighLightActor();
		}
		else
		{
			// Case A - both are null, do nothing 
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighLightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				// Case E - both are the same actor, do nothing
			}
		}
	}
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


