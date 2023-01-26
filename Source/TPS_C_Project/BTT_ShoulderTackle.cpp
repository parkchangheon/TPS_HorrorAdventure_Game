// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ShoulderTackle.h"
#include "MyAIController.h"
#include "Monster_Monster1.h"
#include "BehaviorTree/BTTaskNode.h"
#include <GameFramework/CharacterMovementComponent.h>

UBTT_ShoulderTackle::UBTT_ShoulderTackle(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("ShoulderTackle");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_ShoulderTackle::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	CurrentPawn = Cast<AMonster_Monster1>(owner_comp.GetAIOwner()->GetPawn());
	CurrentPawn->TackleAttacked.AddUObject(this, &UBTT_ShoulderTackle::ClearAndFinishNode);

	CurrentPawn->Tackle();

	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTT_ShoulderTackle::AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	return EBTNodeResult::Failed;
}

void UBTT_ShoulderTackle::ClearAndFinishNode()
{
	CurrentPawn->GetCharacterMovement()->GravityScale = 1.f;
	CanExit = true;
}

void UBTT_ShoulderTackle::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaSeconds)
{
	Super::TickTask(owner_comp, node_memory, DeltaSeconds);
	if (CanExit) {
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	}
}