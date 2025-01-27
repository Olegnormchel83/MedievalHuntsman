// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMMovement.generated.h"

class IMHMStamina;

UENUM(BlueprintType)
enum class EMHMMovementType : uint8
{
    Walking = 0,
    Running,
    Sprinting
};

UINTERFACE(MinimalAPI)
class UMHMMovement : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMMovement
{
    GENERATED_BODY()

public:
    virtual bool IsInAir() const = 0;
    virtual void SetStamina(IMHMStamina* InStamina) = 0;
    virtual void SetMovementType(const EMHMMovementType& InMovementType) = 0;
    virtual void SetCanMove() = 0;
    virtual void ResetCanMove() = 0;
    virtual bool CanMove() const = 0;
};
