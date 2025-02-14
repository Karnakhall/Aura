// Copyright Karnakhall

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	/** Begin AActor Interface*/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface*/
private:
	virtual void InitAbilityActorInfo() override;	// Init ability actor info
};
