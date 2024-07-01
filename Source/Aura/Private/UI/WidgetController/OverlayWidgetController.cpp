// Copyright Karnakhall


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);	// Cast the AttributeSet to an Aura AttributeSet

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());	// Broadcast the health
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());	// Broadcast the max health
}
