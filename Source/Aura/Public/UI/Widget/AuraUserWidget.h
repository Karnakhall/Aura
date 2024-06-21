// Copyright Karnakhall

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;	// UObject is the base class for all objects in Unreal Engine
protected:
	UFUNCTION(BlueprintImplementableEvent)	// BlueprintImplementableEvent is a macro that allows you to call a function from a blueprint
	void WidgetControllerSet();	// Function that is called when the WidgetController is set
	
};
