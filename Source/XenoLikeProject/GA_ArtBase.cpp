// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ArtBase.h"
#include <string>

const FGameplayTagContainer* UGA_ArtBase::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset(); // MutableTags writes to the TempCooldownTags on the CDO so clear it in case the ability cooldown tags change (moved to a different slot)
	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}
	MutableTags->AppendTags(CooldownTags);
	return MutableTags;
}

void UGA_ArtBase::ApplyCooldown(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo
) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		if (GEngine)
		{
			FString s = FString::SanitizeFloat(CooldownDuration.GetValueAtLevel(GetAbilityLevel()));
			GEngine->AddOnScreenDebugMessage(
				-1,           // 一意のキー（-1で常に新しいメッセージとして表示）
				5.0f,         // 表示時間（秒）
				FColor::Red,  // 文字列の色
				s // 表示するテキスト
			);

			
		}
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Cooldown")), CooldownDuration.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);

		if (GEngine) {
			FString t = SpecHandle.Data.Get()->DynamicGrantedTags.GetByIndex(0).GetTagName().ToString();
			GEngine->AddOnScreenDebugMessage(
				-1,           // 一意のキー（-1で常に新しいメッセージとして表示）
				5.0f,         // 表示時間（秒）
				FColor::Red,  // 文字列の色
				t // 表示するテキスト
			);
		}
	}
}