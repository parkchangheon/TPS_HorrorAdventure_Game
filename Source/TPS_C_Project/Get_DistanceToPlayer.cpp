// Fill out your copyright notice in the Description page of Project Settings.


#include "Get_DistanceToPlayer.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


UGet_DistanceToPlayer::UGet_DistanceToPlayer()
{
	NodeName = TEXT("Get Distance To Player");
}

void UGet_DistanceToPlayer::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	DistanceToPlayer = cont->GetPawn()->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}