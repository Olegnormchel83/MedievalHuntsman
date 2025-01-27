// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MHMCharacter.generated.h"

class UMHMAHealthComponent;
class UMHMInventoryComponent;
class UMHMStartingItemsComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    explicit AMHMCharacter(const FObjectInitializer& ObjInit);

    UMHMAHealthComponent* GetHealthComponent() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMAHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMInventoryComponent* InventoryComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMStartingItemsComponent* StartingItemsComponent;

private:
    void Dead();
};
