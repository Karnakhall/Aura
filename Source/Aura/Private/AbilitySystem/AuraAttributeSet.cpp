// Copyright Karnakhall


#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"

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

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);	// Replicate Strength attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);	// Replicate Intelligence attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);	// Replicate Resilience attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);	// Replicate Vigor attribute

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

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = the target of the effect (owner of this AS(attributeSet))

	Props.EffectContextHandle  = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();



	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())	// Check if the SourceASC is valid and the Avatar Actor is valid
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();	// Get the Avatar Actor of the Source
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();	// Get the Player Controller of the Source
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();	// Get the Controller of the Source
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());	// Cast the Source Avatar Actor to a Character
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();	// Get the Avatar Actor of the Target
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();	// Get the Player Controller of the Target
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);	// Cast the Target Avatar Actor to a Character
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);	// Get the Ability System Component of the Target
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);	// Call the parent class's PostGameplayEffectExecute function

	FEffectProperties Props;
	SetEffectProperties(Data, Props);	// Set the Effect Properties

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, FString::Printf(TEXT("Health: %f"), GetHealth()));	// Print a message to the screen
		//SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));	// Clamp the Health between 0 and MaxHealth if it doesn't change before
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, FString::Printf(TEXT("Mana: %f"), GetMana()));	// Print a message to the screen
		//SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));	// Clamp the Mana between 0 and MaxMana if it doesn't change before
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

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}


