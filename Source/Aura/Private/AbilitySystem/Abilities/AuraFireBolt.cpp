// Copyright Karnakhall


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));	// FMath::Abs give us absolute value
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with a chance to burn</>"),
			
			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolts of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL: </>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of FireBolts
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: </>"

		// Damage
		"<Damage>%d</><Default> fire damage with a chance to burn</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);		// Get the socket location from the combat interface
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();		// Get the rotation of the projectile
	//Rotation.Pitch = 0.f;		// Set the pitch to 0.f beacouse wa want to shoot our projectile near the ground
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);
	

	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	if (NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0, 0, 20);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
				Start,
				Start + Direction * 75.f,
				1,
				FLinearColor::Red,
				120.f,
				1);
		}
	}
	else
	{
		// Single projectile
		const FVector Start = SocketLocation + FVector(0, 0, 20);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
			Start,
			Start + Forward * 75.f,
			1,
			FLinearColor::Red,
			120.f,
			1);
	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
		SocketLocation,
		SocketLocation + Forward * 100.f,
		1,
		FLinearColor::Gray,
		120.f,
		1);

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
		SocketLocation,
		SocketLocation + LeftOfSpread * 100.f,
		1,
		FLinearColor::Gray,
		120.f,
		1);

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
		SocketLocation,
		SocketLocation + RightOfSpread * 100.f,
		1,
		FLinearColor::Gray,
		120.f,
		1);
}
