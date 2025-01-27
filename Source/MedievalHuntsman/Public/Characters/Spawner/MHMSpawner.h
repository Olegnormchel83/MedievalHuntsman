// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MHMSpawner.generated.h"

class UBoxComponent;

UCLASS()
class MEDIEVALHUNTSMAN_API AMHMSpawner final : public AActor
{
    GENERATED_BODY()

public:
    AMHMSpawner();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Settings")
    UBoxComponent* BoxComponent;

    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings")
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    uint32 Count = 1;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Seconds"))
    float CheckRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Settings|Level", meta = (ClampMin = "1", UIMin = "1"))
    uint32 MinLevel = 1;

    UPROPERTY(EditAnywhere, Category = "Settings|Level", meta = (ClampMin = "2", UIMin = "2"))
    uint32 MaxLevel = 3;

    UPROPERTY()
    TArray<AActor*> Actors;

    FTimerHandle RespawnTimerHandle;

    void Spawn();
    uint32 GenerateAnimalLevel() const;
    FVector GetSpawnLocation() const;
    void Check();
};
