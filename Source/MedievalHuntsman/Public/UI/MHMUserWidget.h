// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MHMUserWidget.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();
    void Hide();

protected:
    UPROPERTY(Transient, meta = (BindWidgetAnimOptioanl))
    UWidgetAnimation* HideAnimation;

    virtual void Update();
    FTimerManager& GetWorldTimerManager() const;

private:
    FWidgetAnimationDynamicEvent OnAnimationFinishedEvent;

    UFUNCTION()
    void HideAnimationFinished();
};
