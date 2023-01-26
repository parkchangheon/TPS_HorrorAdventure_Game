// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "MasterChara_Monster.h"
#include "BTT_Chase_Player.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTT_Chase_Player : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_Chase_Player(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

};
