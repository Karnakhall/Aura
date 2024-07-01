// Copyright Karnakhall

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayEffect.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);	// Delegate to broadcast when the health changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);	// Delegate to broadcast when the max health changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);	// Delegate to broadcast when the mana changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);	// Delegate to broadcast when the mana changes

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;	// Function to broadcast the initial values
	virtual void BindCallbacksToDependencies() override;	// Function to bind the callbacks to the dependencies

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;	// Function to call when the health changes
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;	// Function to call when the max health changes
	void ManaChanged(const FOnAttributeChangeData& Data) const;	// Function to call when the mana changes
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;	// Function to call when the max mana changes
};
