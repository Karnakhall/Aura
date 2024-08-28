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
	//MessageWidgetRowDelegate.Broadcast(FUIWidgetRow* Row);	// Broadcast the message widget row

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, );	// Add a delegate to the health attribute
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);	// Cast the AttributeSet to an Aura AttributeSet

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);	// Broadcast the health
			}
		
		);	// Add a delegate to the health attribute
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);		// Broadcast the max health
			}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);	// Broadcast the mana
			}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) 
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);	// Broadcast the max mana
			}
		);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) 
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// For example, say that Tag = Message.HealthPotion

				//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag)) // Check if the tag matches the message tag
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);	// Get the row from the DataTable by tag
					MessageWidgetRowDelegate.Broadcast(*Row);	// Broadcast the row
				}

				/*const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());	// Create a message with the tag
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Emerald, Msg);	// Print the tag to the screen*/
			}
		}
	);	// Add a lambda to the EffectAssetTags delegate
}


