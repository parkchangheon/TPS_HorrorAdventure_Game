// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWidget.h"

void UDoorWidget::DecrementSnake()
{
	if (Snake1->IsVisible()) {
		Snake1->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else if (Snake2->IsVisible()) {
		Snake2->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else if (Snake3->IsVisible()) {
		Snake3->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else if (Snake4->IsVisible()) {
		Snake4->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
		return;
}

void UDoorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind delegates here.
}

void UDoorWidget::SetCanvasVisibillity(ESlateVisibility Visibillity)
{
	CanvasPanel_0->SetVisibility(Visibillity);
}