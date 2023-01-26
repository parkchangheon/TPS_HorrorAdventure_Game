// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MasterChara_Monster.h"
#include "BTT_SargentJump.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTT_SargentJump : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

private:
	class AMonster_Monster1* CurrentPawn;
	bool CanExit=false;
public:
	UBTT_SargentJump(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	void TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory ,float DeltaSeconds) override;
private:
	void ClearAndFinishNode();

};
