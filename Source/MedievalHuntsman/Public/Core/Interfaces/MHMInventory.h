// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMInventory.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryChanged);

UINTERFACE(MinimalAPI)
class UMHMInventory : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMInventory
{
    GENERATED_BODY()

public:
    virtual void AddItem(const FName& RowName, const uint32 Count = 1) = 0;
    virtual void TransferFromInventory(IMHMInventory* OtherInventory) = 0;
    virtual const TMap<FName, uint32>& GetItems() const = 0;
    virtual bool HasItem(const FName& RowName) const = 0;
    virtual uint32 GetCountByRowName(const FName& RowName) const = 0;
    virtual bool RemoveItem(const FName& RowName, const uint32 Count = 1) = 0;
    virtual FOnInventoryChanged& OnInventoryChanged() = 0;
};
