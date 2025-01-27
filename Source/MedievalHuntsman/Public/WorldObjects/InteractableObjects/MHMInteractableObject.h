// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/MHMWorldObject.h"
#include "Core/Interfaces/MHMInteract.h"
#include "MHMInteractableObject.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMInteractableObject : public AMHMWorldObject, public IMHMInteract
{
    GENERATED_BODY()

public:
    AMHMInteractableObject();

    virtual void Interact(AActor* OtherActor) override final;
    virtual void OnEnter() override;
    virtual void OnLeave() override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;

    virtual void DoInteract(AActor* OtherActor);
    virtual bool CanInteract() const;
};
