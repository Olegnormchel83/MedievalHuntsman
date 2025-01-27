// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/MHMCharacter.h"
#include "MHMAnimalCharacter.generated.h"

class UBoxComponent;
class UMHMAnimalStatsComponent;
struct FAIStimulus;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMAnimalCharacter final : public AMHMCharacter
{
    GENERATED_BODY()

public:
    explicit AMHMAnimalCharacter(const FObjectInitializer& ObjInit);

    virtual void BeginPlay() override;

    bool IsAgressive() const;
    void SetAnimalLevel(float InLevel);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* BlockCollisionBody;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* BlockCollisionHead;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UMHMAnimalStatsComponent* AnimalStatsComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    bool bIsAgressive = false;
};
