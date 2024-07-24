// Copyright Karnakhall


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);	// Bind the EffectApplied function to the OnGameplayEffectAppliedDelegateToSelf
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Emerald, TEXT("Effect Applied!"));	// Print "Effect Applied!" to the screen
	FGameplayTagContainer TagContainer;		// Create a new tag container
	EffectSpec.GetAllAssetTags(TagContainer);	// Get all the tags from the effect
	for (const FGameplayTag& Tag : TagContainer)
	{
		//TODO: Broadcast the tag to the widget controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Emerald, Msg);	// Print the tag to the screen
	}

}
