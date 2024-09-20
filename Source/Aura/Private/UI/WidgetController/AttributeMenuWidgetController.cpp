// Copyright Karnakhall


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
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
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);		// Find the attribute info for the tag
		Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AS);		// Set the attribute value
		AttributeInfoDelegate.Broadcast(Info);		// Broadcast the attribute info
	}
	
}
