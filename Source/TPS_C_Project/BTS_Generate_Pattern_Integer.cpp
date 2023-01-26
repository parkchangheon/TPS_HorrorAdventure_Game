// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_Generate_Pattern_Integer.h"
#include "MyAIController.h"

UBTS_Generate_Pattern_Integer::UBTS_Generate_Pattern_Integer()
{
	NodeName = TEXT("Generate Pattern Integer");
	bNotifyBecomeRelevant = true;
}

void UBTS_Generate_Pattern_Integer::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	AMyAIController* const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (MaxInt == 0) {UE_LOG(LogTemp,Error,TEXT("MaxInt Is Zero, Check for it")) return; }
	int32 val = MiniMumInt + rand() % MaxInt;
	cont->GetBlackboardComponent()->SetValueAsInt(TEXT("Pattern Integer"), uint8(val));
}
