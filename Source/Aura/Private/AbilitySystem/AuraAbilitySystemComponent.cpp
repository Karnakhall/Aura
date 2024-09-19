// Copyright Karnakhall


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);	// Bind the EffectApplied function to the OnGameplayEffectAppliedDelegateToSelf
	
	/* Debug meesage
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();		// Get the Aura Gameplay Tags
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));	// Print the tag to the screen
	*/
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Emerald, TEXT("Effect Applied!"));	// Print "Effect Applied!" to the screen
	FGameplayTagContainer TagContainer;		// Create a new tag container
	EffectSpec.GetAllAssetTags(TagContainer);	// Get all the tags from the effect

	EffectAssetTags.Broadcast(TagContainer);	// Broadcast the tags to the delegate

}
