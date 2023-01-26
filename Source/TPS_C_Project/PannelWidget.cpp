// Fill out your copyright notice in the Description page of Project Settings.


#include "PannelWidget.h"

void UPannelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
}



FReply UPannelWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Right && !IsAnyAnimationPlaying())
	{
		PlayAnimation(Right);
		if (ButtonRequired) {
			PressedKey[PannelCnt] = 3;
			return FReply::Handled();
		}
		
	}

	if (InKeyEvent.GetKey() == EKeys::Left && !IsAnyAnimationPlaying())
	{
		PlayAnimation(Left);
		if (ButtonRequired) {
			PressedKey[PannelCnt] = 9;
			return FReply::Handled();
		}
	}

	if (InKeyEvent.GetKey() == EKeys::Up && !IsAnyAnimationPlaying())
	{
		PlayAnimation(Up);
		if (ButtonRequired) {
			PressedKey[PannelCnt] = 12;
			return FReply::Handled();
		}
	}

	if (InKeyEvent.GetKey() == EKeys::Down && !IsAnyAnimationPlaying())
	{
		PlayAnimation(Down);
		if (ButtonRequired) {
			PressedKey[PannelCnt] = 6;
			return FReply::Handled();
		}
	}

	return FReply::Handled();
}