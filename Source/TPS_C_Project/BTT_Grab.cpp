// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Grab.h"
#include "MyAIController.h"
#include "Monster_Monster1.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <DrawDebugHelpers.h>

UBTT_Grab::UBTT_Grab(FObjectInitializer const& object_initializer)
{
	bNotifyTick = true;

	NodeName = TEXT("Grab");
}

EBTNodeResult::Type UBTT_Grab::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	CurrentPawn = Cast<AMonster_Monster1>(owner_comp.GetAIOwner()->GetPawn());
	
	CurrentPawn->GrabEnd.AddUObject(this, &UBTT_Grab::ClearAndFinishNode);
	CurrentPawn->Grap();

	return EBTNodeResult::InProgress;

}

void UBTT_Grab::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaSeconds)
{
	Super::TickTask(owner_comp, node_memory, DeltaSeconds);
	if (CanExit) {
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UBTT_Grab::AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	return EBTNodeResult::Failed;
}

void UBTT_Grab::ClearAndFinishNode()
{
	CanExit = true;
}

