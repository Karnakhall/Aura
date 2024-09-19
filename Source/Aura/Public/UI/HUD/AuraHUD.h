// Copyright Karnakhall

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class UAuraUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:


	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);	// Function to get the overlay widget controller
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);	// Function to get the attribute menu widget controller

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);	// Function to initialize the overlay

protected:
	

private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;	// The class of the overlay widget

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;	// The overlay widget controller

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;	// The class of the overlay widget controller

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;	// The attribute menu widget controller

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;	// The class of the attribute menu widget controller
};
