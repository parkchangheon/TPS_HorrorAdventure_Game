// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_SargentJump.h"
#include "MyAIController.h"
#include "Monster_Monster1.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <DrawDebugHelpers.h>

UBTT_SargentJump::UBTT_SargentJump(FObjectInitializer const& object_initializer)
{
	bNotifyTick = true;
	bIgnoreRestartSelf = true;
	NodeName = TEXT("Sargent Jump");
}

EBTNodeResult::Type UBTT_SargentJump::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	CurrentPawn = Cast<AMonster_Monster1>(owner_comp.GetAIOwner()->GetPawn());
	CurrentPawn->JumpAttacked.AddUObject(this, &UBTT_SargentJump::ClearAndFinishNode);

	CurrentPawn->SargentJump();
	
	return EBTNodeResult::InProgress;
	
}

void UBTT_SargentJump::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaSeconds)
{
	Super::TickTask(owner_comp, node_memory, DeltaSeconds);
	if (CanExit) {
		CanExit = false;
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UBTT_SargentJump::AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	return EBTNodeResult::Failed;
}

void UBTT_SargentJump::ClearAndFinishNode()
{

	CurrentPawn->GetCharacterMovement()->GravityScale = 1.f;
	CanExit = true;
}
