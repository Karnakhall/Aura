// Copyright Karnakhall

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"
//#include "NiagaraSystem.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;
class UNiagaraSystem;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;	// Get ability system component
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }	// Get attribute set. IAbilitySystem implementation

	/** Combat Interface */
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;		//It will be ragdoll
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;	// Get combat socket location. ICombatInterface implementation
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	/** End Combat Interface */

	UFUNCTION(NetMulticast, Reliable)	//For network
	virtual void MulticastHandleDeath();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;	// Weapon mesh

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;	// Weapon tip socket name

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	bool bDead = false;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


	virtual void InitAbilityActorInfo();	// Init ability actor info

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes;	// Default primary attributes

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultSecondaryAttributes;	// Default secondary attributes

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;	// Apply effect to self
	virtual void InitializeDefaultAttributes() const;	// Initialize default attributes

	void AddCharacterAbilities();	// Add character abilities

	/* Disssolve Effects */

	void Dissolve();	// Swap up material. It will be create dynamic material instance based on material instances.

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UNiagaraSystem* BloodEffect;

private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;		// Array of startup abilities

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
