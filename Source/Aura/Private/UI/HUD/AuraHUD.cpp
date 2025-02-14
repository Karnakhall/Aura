// Copyright Karnakhall


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)	// Function to get the overlay widget controller
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);	// Create a new overlay widget controller
		OverlayWidgetController->SetWidgetControllerParams(WCParams);	// Set the parameters for the widget controller
		OverlayWidgetController->BindCallbacksToDependencies();	// Bind the callbacks to the dependencies. Then we will be able to call the functions when the attributes change in game
		//OverlayWidgetController->AddToRoot();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);	// Create a new attribute menu widget controller
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);	// Set the parameters for the widget controller
		AttributeMenuWidgetController->BindCallbacksToDependencies();	// Bind the callbacks to the dependencies. Then we will be able to call the functions when the attributes change in game
		//AttributeMenuWidgetController->AddToRoot();
	}
	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)	//
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));	// Check if the overlay widget class is initialized
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class, uninitialized, please fill out BP_AuraHUD"));	// Check if the overlay widget controller class is initialized

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);	// Create a new user widget
	OverlayWidget = Cast<UAuraUserWidget>(Widget);	// Cast the widget to an Aura user widget

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);	// Create a new widget controller parameters
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);	// Get the overlay widget controller

	OverlayWidget->SetWidgetController(WidgetController);	// Set the widget controller for the overlay widget
	WidgetController->BroadcastInitialValues();	// Broadcast the initial values for the widget controller
	Widget->AddToViewport();
}

