// Copyright Karnakhall


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
