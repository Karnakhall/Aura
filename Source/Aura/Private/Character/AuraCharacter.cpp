// Copyright Karnakhall

#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;	// Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);	// ...at this rotation rate
	GetCharacterMovement()->bConstrainToPlane = true;	// Constrain movement to the XY plane
	GetCharacterMovement()->bSnapToPlaneAtStart = true;	// Snap to the plane at the start


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();		// Get player state
	check(AuraPlayerState);		// Check player state
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);	// Init ability actor info from GetAbilitySystemComponent and then InitAbilityActorInfo
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();	// Set ability actor info
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();	// Set ability system component
	AttributeSet = AuraPlayerState->GetAttributeSet();	// Set attribute set
	

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();	// Initialize default attributes
}
