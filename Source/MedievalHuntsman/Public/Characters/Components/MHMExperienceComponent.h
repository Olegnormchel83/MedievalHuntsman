// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Characters/Interfaces/MHMExperience.h"
#include "MHMExperienceComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMExperienceComponent final : public UMHMActorComponent, public IMHMExperience
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable)
    virtual void AddExperience(const int32 AddValue) override;

    UFUNCTION(BlueprintCallable)
    virtual void ReduceExperience(const int32 ReduceValue) override;

    virtual int32 CalculateExperienceForNextLevel(const int32 InLevel) override;
    virtual int32 GetCurrentLevel() const override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "ExperienceSettings", meta = (UIMin = "1", ClampMin = "1"))
    int32 CurrentLevel = 1;

    UPROPERTY(EditDefaultsOnly, Category = "ExperienceSettings", meta = (UIMin = "1", ClampMin = "1"))
    int32 CurrentExperience = 1;

    UPROPERTY(EditDefaultsOnly, Category = "ExperienceSettings", meta = (UIMin = "1", ClampMin = "1"))
    int32 ExperienceForNextLevel;

    UPROPERTY(EditDefaultsOnly, Category = "ExperienceSettings", meta = (UIMin = "500", ClampMin = "500"))
    int32 ExpForLevelTwo = 1000;
};
