// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_PlayDialog.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UBTT_PlayDialog : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsPlayer = false;

	bool CanExit = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DialogTextNumber;

	class AMaster_NPC* TargetPawn;
	
public:
	UBTT_PlayDialog(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	
	UFUNCTION()
	void EndThis();

	void TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaSeconds) override;
};
