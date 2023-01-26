
#include "BTService_SetSpeed.h"
#include "MyAIController.h"
#include "StatComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

UBTService_SetSpeed::UBTService_SetSpeed()
{
	NodeName = TEXT("SetSpeed");
	bNotifyBecomeRelevant = true;
	//CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
}

void UBTService_SetSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (CurrentPawn == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
		return;
	}
	

	switch (MonsterState) {
	case State::Idle:
		//CurrentPawn->GetCharacterMovement()->MaxWalkSpeed = CurrentPawn->StatComponent->GetBaseSpeed();
		break;
	case State::Suspect:
		//CurrentPawn->GetCharacterMovement()->MaxWalkSpeed = CurrentPawn->StatComponent->GetCrouchSpeed();
		break;
	case State::Detected:
		//CurrentPawn->GetCharacterMovement()->MaxWalkSpeed = CurrentPawn->StatComponent->GetRunSpeed();
		break;

	}
}
