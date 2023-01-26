// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PannelWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UPannelWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidgetAnim) ,meta = (AllowPrivateAccess = true), Transient)
	UWidgetAnimation* Right;

	UPROPERTY(meta = (BindWidgetAnim) ,meta = (AllowPrivateAccess = true), Transient)
	UWidgetAnimation* Left;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true), Transient)
	UWidgetAnimation* Up;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true), Transient)
	UWidgetAnimation* Down;
protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
public:
	virtual void NativeConstruct() override;
	bool ButtonRequired = false;
	int32 PressedKey[4] = { -1,-1,-1,-1 };
	int32 PannelCnt = 0;

};
