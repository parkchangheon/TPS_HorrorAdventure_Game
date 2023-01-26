// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "NPC_Controller.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBehaviorTree* DialogTree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlackboardData* BB;

public:
	UFUNCTION(BlueprintCallable)
	void PlayTree();

	UFUNCTION(BlueprintCallable)
	void EndDialog();

};
