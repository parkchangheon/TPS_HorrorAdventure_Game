// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EndDialog.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTT_EndDialog : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_EndDialog();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

};
