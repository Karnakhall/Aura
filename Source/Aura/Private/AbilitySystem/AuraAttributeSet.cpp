// Copyright Karnakhall


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const	// Register variables for replication
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);		// Call the parent class's GetLifetimeReplicatedProps function

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);	// Replicate Health attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);	// Replicate MaxHealth attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);	// Replicate Mana attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);	// Replicate MaxMana attribute
}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);	// Call the parent class's PreAttributeChange function

	if (Attribute == GetHealthAttribute())	// If the attribute is Health
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());	// Clamp the new value between 0 and MaxHealth
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewValue);	// Log a message
	}
	
	if (Attribute == GetManaAttribute())	// If the attribute is Mana
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());	// Clamp the new value between 0 and MaxMana
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);	// Log a message
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const	
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);		// OnRep_Health function OldHealth compare with the Health attribute
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);		// OnRep_MaxHealth function OldMaxHealth compare with the Health attribute
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);		// OnRep_Mana function OldMana compare with the Mana attribute
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);		// OnRep_MaxMana function OldMaxMana compare with the MaxMana attribute
}
