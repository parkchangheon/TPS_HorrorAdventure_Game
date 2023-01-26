// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Chase_Player.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "MyAIController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>


UBTT_Chase_Player::UBTT_Chase_Player(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTT_Chase_Player::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTT_Chase_Player::AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	Cast<AMasterChara_Monster>(cont->GetPawn())->GetCharacterMovement()->StopMovementImmediately();

	FinishLatentTask(owner_comp, EBTNodeResult::Aborted);
	return EBTNodeResult::Aborted;
}