// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick_Master.h"
#include "Gimmick_Doll_Box.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AGimmick_Doll_Box : public AGimmick_Master
{
	GENERATED_BODY()

public:
	AGimmick_Doll_Box();

	UFUNCTION(BlueprintImplementableEvent)
	void Interact_Gimmick();

	virtual void Interact_Gimmick_Call() override;
	
};
