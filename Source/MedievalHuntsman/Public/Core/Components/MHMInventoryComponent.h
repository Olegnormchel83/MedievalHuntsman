// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Core/Interfaces/MHMInventory.h"
#include "MHMInventoryComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMInventoryComponent final : public UMHMActorComponent, public IMHMInventory
{
    GENERATED_BODY()

public:
    virtual void AddItem(const FName& RowName, const uint32 Count = 1) override;
    virtual void TransferFromInventory(IMHMInventory* OtherInventory) override;
    virtual const TMap<FName, uint32>& GetItems() const override;
    virtual bool HasItem(const FName& RowName) const override;
    virtual uint32 GetCountByRowName(const FName& RowName) const override;
    virtual bool RemoveItem(const FName& RowName, const uint32 Count = 1) override;
    virtual FOnInventoryChanged& OnInventoryChanged() override;

private:
    TMap<FName, uint32> Items;
    FOnInventoryChanged OnInventoryChangedEvent;
};
