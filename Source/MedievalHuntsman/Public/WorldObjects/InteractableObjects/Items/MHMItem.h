// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/InteractableObjects/MHMInteractableObject.h"
#include "MHMItem.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMItem : public AMHMInteractableObject
{
    GENERATED_BODY()

public:
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    virtual void DoInteract(AActor* OtherActor) override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings")
    FDataTableRowHandle ItemRow;

    void InitMesh();
};
