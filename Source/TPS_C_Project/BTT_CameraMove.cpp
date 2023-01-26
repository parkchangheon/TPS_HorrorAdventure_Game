// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CameraMove.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "MyAIController.h"
#include "Camera/CameraComponent.h"

UBTT_CameraMove::UBTT_CameraMove(FObjectInitializer const& object_initializer)
{
	bNotifyTick = false;
	Custom = false;
	VectorToSelect = VectorSelection::ConversationVector1;
	ObjectToSelect = InterpObject::NPC;
	CustomTransform = FTransform(FRotator(0,0,0), FVector(0,0,0));
	NodeName = TEXT("CameraMove");
}



EBTNodeResult::Type UBTT_CameraMove::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (ObjectToSelect == InterpObject::Player) {
		ObjectToInterp = Cast<AMaster_NPC>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	else if(ObjectToSelect == InterpObject::NPC) {
		ObjectToInterp = Cast<AMaster_NPC>(owner_comp.GetAIOwner()->GetPawn());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Object To Interp Value In BTT_CameraMove.cpp Was Going Wrong Check it"));
		return EBTNodeResult::Failed;
	}

	//플레이어를 적절한 위치와 각도 변경
	{
		FVector FaceNPCLocation =
			(owner_comp.GetAIOwner()->GetPawn()->GetActorLocation()) +
			(owner_comp.GetAIOwner()->GetPawn()->GetActorForwardVector() * 100);
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(FaceNPCLocation);

		FRotator FaceNPCRotator = UKismetMathLibrary::FindLookAtRotation(
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),
			owner_comp.GetAIOwner()->GetPawn()->GetActorLocation()
		);
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorRotation(FaceNPCRotator);
	}

	
	if (Custom)
	{
		ObjectToInterp->FollowCamera->SetRelativeTransform(CustomTransform);
		Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController())->SetViewTarget(ObjectToInterp);
		return EBTNodeResult::Succeeded;
	}
	else {
		FTransform SelectedTranform;
		switch (VectorToSelect) {
		case VectorSelection::ConversationVector1:
			SelectedTranform = ObjectToInterp->CameraTransform1;
			break;
		case VectorSelection::ConversationVector2:
			SelectedTranform = ObjectToInterp->CameraTransform2;
			break;
		case VectorSelection::ConversationVector3:
			SelectedTranform = ObjectToInterp->CameraTransform3;
			break;
		default:
			break;
		}
		ObjectToInterp->FollowCamera->SetRelativeTransform(SelectedTranform);
		Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController())->SetViewTarget(ObjectToInterp);
		return EBTNodeResult::Succeeded;
	}
}

