// Copyright Karnakhall


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)	// Function to set the parameters for the widget controller
{
	PlayerController = WCParams.PlayerController;	// Set the PlayerController to the PlayerController from the WCParams
	PlayerState = WCParams.PlayerState;	// Set the PlayerState to the PlayerState from the WCParams
	AbilitySystemComponent = WCParams.AbilitySystemComponent;	// Set the AbilitySystemComponent to the AbilitySystemComponent from the WCParams
	AttributeSet = WCParams.AttributeSet;	// Set the AttributeSet to the AttributeSet from the WCParams
}

void UAuraWidgetController::BroadcastInitialValues()
{

}
