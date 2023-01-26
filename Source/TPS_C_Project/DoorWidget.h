// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "DoorWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UDoorWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* Snake1;

	UPROPERTY(meta = (BindWidget))
	USizeBox* Snake2;

	UPROPERTY(meta = (BindWidget))
	USizeBox* Snake3;

	UPROPERTY(meta = (BindWidget))
	USizeBox* Snake4;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_0;
public:
	void SetCanvasVisibillity(ESlateVisibility Visibillity);
	void DecrementSnake();
	virtual void NativeConstruct() override;
	
};
