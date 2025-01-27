// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMStartingItemsComponent.generated.h"

USTRUCT(BlueprintType)
struct FStartingItem
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly)
    FDataTableRowHandle ItemRow;

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
    float Probability = 1.0f;

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0", ClampMax = "30", UIMax = "30"))
    uint32 Count = 1;
};

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMStartingItemsComponent : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TArray<FStartingItem> StartingItems;

    void AddStartingItems();
};
