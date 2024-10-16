// Copyright Karnakhall


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)

	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);		// Cast the AssetManager to our custom class

	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();

	// This is requierd to use Target Data
	UAbilitySystemGlobals::Get().InitGlobalData();
}
