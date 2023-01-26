// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PlayDialog.h"
#include "Master_NPC.h"
#include <Components/AudioComponent.h>
#include "MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UBTT_PlayDialog::UBTT_PlayDialog(FObjectInitializer const& object_initializer)
{
	bNotifyTick = true;
	NodeName = TEXT("PlayDialog");
}

EBTNodeResult::Type UBTT_PlayDialog::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (IsPlayer) {
		TargetPawn = Cast<AMaster_NPC>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	else {
		TargetPawn = Cast<AMaster_NPC>(owner_comp.GetAIOwner()->GetPawn());
	}
	
	if (!TargetPawn) { return EBTNodeResult::Failed; }

	//UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->DisableMovement();
	
	TargetPawn->ConversationManager->PlayDialog(DialogTextNumber);
	
	//↓임시 태스크 종료 로직 추후 새로운 로직(마우스 클릭하면 끝난다 등) 필요
	TargetPawn->Audio->OnAudioFinished.AddDynamic(this, &UBTT_PlayDialog::EndThis);
	

	return EBTNodeResult::InProgress;
	
}


void UBTT_PlayDialog::EndThis()
{
	CanExit = true;
}

void UBTT_PlayDialog::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaSeconds)
{
	Super::TickTask(owner_comp, node_memory, DeltaSeconds);
	if (CanExit) {
		CanExit = false;
		TargetPawn->Audio->OnAudioFinished.RemoveDynamic(this, &UBTT_PlayDialog::EndThis);
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	}
}
