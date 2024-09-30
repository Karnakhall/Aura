// Copyright Karnakhall


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);	// Cast the attribute set to the Aura attribute set
	check(AttributeInfo);		// Check if the attribute info is valid
	for (auto& Pair : AS->TagsToAttributes)		// Iterate over the tags to attributes map
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());		// Broadcast the attribute info
			}
		);
	}
	
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	/*FAuraAttributeInfo StrengthInfo = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);

	StrengthInfo.AttributeValue = AS->GetStrength();

	AttributeInfoDelegate.Broadcast(StrengthInfo);
	*/

	for (auto& Pair : AS->TagsToAttributes)		// Iterate over the tags to attributes map
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());		// Broadcast the attribute info
	}
	
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);		// Find the attribute info for the tag
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);		// Get the numeric value of the attribute
	AttributeInfoDelegate.Broadcast(Info);		// Broadcast the attribute info
}
