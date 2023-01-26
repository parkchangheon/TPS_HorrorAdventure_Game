// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MasterChara_Monster.h"
#include "BTService_SetSpeed.generated.h"


/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTService_SetSpeed : public UBTService
{
	GENERATED_BODY()
private:
	UBTService_SetSpeed();
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	State MonsterState;

	APawn* CurrentPawn;
};
