// Fill out your copyright notice in the Description page of Project Settings.


#include "Set_Monster_State.h"
#include "MyAIController.h"
#include <BehaviorTree/BlackboardComponent.h>

USet_Monster_State::USet_Monster_State(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Set State");
}


EBTNodeResult::Type USet_Monster_State::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	cont->GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), uint8(state));
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}