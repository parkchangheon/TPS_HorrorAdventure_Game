// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_Generate_Pattern_Integer.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTS_Generate_Pattern_Integer : public UBTService
{
	GENERATED_BODY()
private:
	UBTS_Generate_Pattern_Integer();
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere)
	int32 MaxInt;

	UPROPERTY(EditAnywhere)
	int32 MiniMumInt;
};
