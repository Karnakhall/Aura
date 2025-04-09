// Copyright Karnakhall


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");	// Create ability system component
	AbilitySystemComponent->SetIsReplicated(true);	// Enable replication for ability system component
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);	// Set replication mode for ability system component

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");	// Create attribute set

	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);		// Call the parent class's GetLifetimeReplicatedProps function

	DOREPLIFETIME(AAuraPlayerState, Level);	// Replicate Level attribute
	DOREPLIFETIME(AAuraPlayerState, XP);	// Replicate Level attribute
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);	// Replicate Level attribute
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);	// Replicate Level attribute
	/*DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, Experience, COND_None, REPNOTIFY_Always);	// Replicate Experience attribute
	DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, Gold, COND_None, REPNOTIFY_Always);	// Replicate Gold attribute
	DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, AbilityPoints, COND_None, REPNOTIFY_Always);	// Replicate AbilityPoints attribute
	DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, AttributePoints, COND_None, REPNOTIFY_Always);	// Replicate AttributePoints attribute
	*/
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToAttributePoints(int32 InAttribute)	//Maybe I should change name InAttribute to InPoints
{
	AttributePoints += InAttribute;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 InSpell)	//Maybe I should change name InSpell to InPoints
{
	SpellPoints += InSpell;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetAttributePoints(int32 InAttribute)
{
	AttributePoints = InAttribute;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::SetSpellPoints(int32 InSpell)
{
	SpellPoints = InSpell;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);	//Delegate on a client side
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
