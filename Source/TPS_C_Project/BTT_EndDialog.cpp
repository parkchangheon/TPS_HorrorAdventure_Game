// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EndDialog.h"
#include "NPC_Controller.h"
#include "Master_NPC.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Camera/CameraComponent.h"

UBTT_EndDialog::UBTT_EndDialog()
{
	bNotifyTick = true;
	NodeName = TEXT("EndDialog");
}

EBTNodeResult::Type UBTT_EndDialog::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMaster_NPC* Player = Cast<AMaster_NPC>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	
	Player->FollowCamera->SetRelativeTransform(
		FTransform(
		FRotator(0, 0, 0),
		FVector(0, 0, 0),
		FVector(1, 1, 1)
		)
	);

	Cast<APlayerController>(Player->GetController())->SetViewTarget(Player);
	
	Cast<ANPC_Controller>(owner_comp.GetAIOwner())->EndDialog();
	
	return EBTNodeResult::Succeeded;
}