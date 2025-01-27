// MedievalHuntsman. Author: Olegnormchel


#include "UI/MHMUserWidget.h"

void UMHMUserWidget::Show()
{
    if (IsVisible())
        return;

    SetVisibility(ESlateVisibility::Visible);
}

void UMHMUserWidget::Hide()
{
    if (!IsVisible())
        return;
    if (HideAnimation)
    {
        StopAllAnimations();
        OnAnimationFinishedEvent.BindDynamic(this, &ThisClass::HideAnimationFinished);
        BindToAnimationFinished(HideAnimation, OnAnimationFinishedEvent);
        PlayAnimation(HideAnimation);
    }
    else
    {
        HideAnimationFinished();
    }
}

FTimerManager& UMHMUserWidget::GetWorldTimerManager() const
{
    check(GetWorld());
    return GetWorld()->GetTimerManager();
}

void UMHMUserWidget::HideAnimationFinished()
{
    SetVisibility(ESlateVisibility::Hidden);
}

void UMHMUserWidget::Update()
{
}
