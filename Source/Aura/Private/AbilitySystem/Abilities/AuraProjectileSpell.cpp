// Copyright Karnakhall


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());		// Get the combat interface from the avatar actor
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();		// Get the socket location from the combat interface
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();		// Get the rotation of the projectile
		Rotation.Pitch = 0.f;		// Set the pitch to 0.f beacouse wa want to shoot our projectile near the ground

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set the rotation of the projectile.
		SpawnTransform.SetRotation(Rotation.Quaternion());		// Set the rotation of the projectile, projectile flight where the mouse is pointing

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projctile a Gameplay Effect Spec for causing Damage.

		Projectile->FinishSpawning(SpawnTransform);
	}


}
