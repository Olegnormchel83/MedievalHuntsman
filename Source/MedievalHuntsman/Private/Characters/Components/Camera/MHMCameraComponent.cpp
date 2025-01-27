// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/Camera/MHMCameraComponent.h"
#include "Characters/Interfaces/MHMStamina.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogCameraComponent, All, All);

void UMHMCameraComponent::BeginPlay()
{
    Super::BeginPlay();

    GammaWithNormalStamina = PostProcessSettings.ColorGamma;
    BloomIntensityWithNormalStamina = PostProcessSettings.BloomIntensity;
    VignetteIntensityWithNormalStamina = PostProcessSettings.VignetteIntensity;
}

void UMHMCameraComponent::SetStamina(IMHMStamina* InStamina)
{
    Stamina = InStamina;
    check(Stamina);
    Stamina->OnChangedStamina().AddUObject(this, &ThisClass::StaminaEffects);
}

void UMHMCameraComponent::StaminaEffects()
{
    check(Stamina);
    const float CurrentStamina = Stamina->GetCurrentStamina();
    if (CurrentStamina < StartValueForStamineEffects)
    {
        const float Alpha = UKismetMathLibrary::MapRangeClamped(CurrentStamina, 0, StartValueForStamineEffects, 0, 1);
        const FVector4d GammaValue = FMath::Lerp(GammaWithMinStamina, GammaWithNormalStamina, Alpha);
        const float BloomIntensityValue = FMath::Lerp(BloomIntensityWithMinStamina, BloomIntensityWithNormalStamina, Alpha);
        const float VignetteIntensityValue = FMath::Lerp(VignetteIntensityWithMinStamina, VignetteIntensityWithNormalStamina, Alpha);

        PostProcessSettings.ColorGamma = GammaValue;
        PostProcessSettings.BloomIntensity = BloomIntensityValue;
        PostProcessSettings.VignetteIntensity = VignetteIntensityValue;
    }
}
