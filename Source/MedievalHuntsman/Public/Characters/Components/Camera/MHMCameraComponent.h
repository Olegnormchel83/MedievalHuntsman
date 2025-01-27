// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "MHMCameraComponent.generated.h"

class IMHMStamina;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    void SetStamina(IMHMStamina* InStamina);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float StartValueForStamineEffects = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FVector4d GammaWithMinStamina{0.8f, 0.8f, 1.0f, 1.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float BloomIntensityWithMinStamina = 8.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float VignetteIntensityWithMinStamina = 1.0f;

    IMHMStamina* Stamina;
    FVector4d GammaWithNormalStamina;
    float BloomIntensityWithNormalStamina;
    float VignetteIntensityWithNormalStamina;

    void StaminaEffects();
};
