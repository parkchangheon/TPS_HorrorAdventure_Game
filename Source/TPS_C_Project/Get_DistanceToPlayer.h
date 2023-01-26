// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyAIController.h"
#include "Get_DistanceToPlayer.generated.h"


/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UGet_DistanceToPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UGet_DistanceToPlayer();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	float DistanceToPlayer;
};
