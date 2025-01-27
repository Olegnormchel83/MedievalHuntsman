// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/InteractableObjects/MHMInteractableObject.h"
#include "MHMWeapon.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMWeapon : public AMHMInteractableObject
{
    GENERATED_BODY()

public:
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    virtual void DoInteract(AActor* OtherActor) override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings")
    FDataTableRowHandle WeaponRow;

    void InitMesh();
};
