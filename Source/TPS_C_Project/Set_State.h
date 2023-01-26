// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MasterChara_Monster.h"
#include "Set_State.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API USet_State : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	USet_State(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	State state;
};
