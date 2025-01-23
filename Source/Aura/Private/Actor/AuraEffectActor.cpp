// Copyright Karnakhall
#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"



// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}
/*
void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);		// This is a hack to modify the attribute directly. This is not the correct way to do it.
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
*/
// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)	// This is the function that will apply the effect to the target
{

	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;		// Enemies don't be pickup potion etc. Pickups will be ignore enemies

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);	// Get the Ability System Component of the target actor. Stored in pointer TargetASC.
	if (TargetASC == nullptr) return;	// If the TargetASC is null, return. This is a safety check to prevent crashes.

	check(GameplayEffectClass);	// Check if the GameplayEffectClass is valid. If not, assert.
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();	// Create a new Effect Context Handle
	EffectContextHandle.AddSourceObject(this);	// Add the source object to the Effect Context Handle
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);	// Create a new Effect Spec Handle
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());		// Apply the effect to the target actor. // Apply the Effect Spec Handle to the target actor. Dereference the Effect Spec Handle to get the data and pass it to ApplyGameplayEffectSpecToSelf.

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite; // Check if the effect is infinite
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)	//
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);	// Add the Active Effect Handle to the Active Effect Handles array
	}

	if (!bIsInfinite)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)	// This function will be called when the actor overlaps with another actor
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);		// Apply the instant effect to the target actor
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);		// Apply the duration effect to the target actor
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);		// Apply the infinite effect to the target actor
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)	// This function will be called when the actor ends overlap with another actor
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);		// Apply the instant effect to the target actor
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);		// Apply the duration effect to the target actor
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);		// Apply the infinite effect to the target actor
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);	// Get the Ability System Component of the target actor. Stored in pointer TargetASC.
		if (!IsValid(TargetASC)) return;	// If the TargetASC is not valid, return. This is a safety check to prevent crashes.
		
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;	// Create a new array of ActiveGameplayEffectHandles
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)	// Loop through the ActiveEffectHandles array
		{
			if (TargetASC == HandlePair.Value)	// If the TargetASC is equal to the value of the HandlePair
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);	// Remove the active effect from the target actor
				HandlesToRemove.Add(HandlePair.Key);	// Add the HandlePair.Key to the HandlesToRemove array
			}
		}
		for (auto& Handle : HandlesToRemove)	// Loop through the HandlesToRemove array
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);	// Find and remove the Handle from the ActiveEffectHandles array
		}
	}
}


