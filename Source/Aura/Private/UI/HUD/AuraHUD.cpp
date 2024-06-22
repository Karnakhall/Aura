// Copyright Karnakhall


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)	// Function to get the overlay widget controller
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);	// Create a new overlay widget controller
		OverlayWidgetController->SetWidgetControllerParams(WCParams);	// Set the parameters for the widget controller
		//OverlayWidgetController->AddToRoot();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)	//
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));	// Check if the overlay widget class is initialized
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class, uninitialized, please fill out BP_AuraHUD"));	// Check if the overlay widget controller class is initialized

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);	// Create a new user widget
	OverlayWidget = Cast<UAuraUserWidget>(Widget);	// Cast the widget to an Aura user widget
	


	Widget->AddToViewport();
}

