// Copyright Karnakhall


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);	// Cast the AttributeSet to an Aura AttributeSet

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());	// Broadcast the health
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());	// Broadcast the max health
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());	// Broadcast the mana
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());	// Broadcast the max mana

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, );	// Add a delegate to the health attribute
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);	// Cast the AttributeSet to an Aura AttributeSet

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);	// Add a delegate to the health attribute
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);	// Add a delegate to the max health attribute
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);	// Add a delegate to the mana attribute
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);	// Add a delegate to the max mana attribute

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags) 
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());	// Create a message with the tag
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Emerald, Msg);	// Print the tag to the screen
			}
		}
	);	// Add a lambda to the EffectAssetTags delegate
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);	// Broadcast the health
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);		// Broadcast the max health
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);	// Broadcast the mana
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);	// Broadcast the max mana
}
