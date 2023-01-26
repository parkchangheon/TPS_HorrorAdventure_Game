// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_LeeYul.h"
#include "TPS_C_ProjectCharacter.h"
#include <Runtime/Engine/Classes/GameFramework/Character.h>
#include <Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h>
#include <Perception/AISense_Hearing.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UAnimInstance_LeeYul::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
		PlayerRef = Cast<ATPS_C_ProjectCharacter>(Pawn);
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		
		if (PlayerRef)
		{
			IsFalling = PlayerRef->GetMovementComponent()->IsFalling();
			Vertical = PlayerRef->UpDownVal;
			Horizontal = PlayerRef->LeftRightVal;
			IsDead = PlayerRef->Dead;
			
		}

	}

}

UAnimInstance_LeeYul::UAnimInstance_LeeYul()
{
	
}

void UAnimInstance_LeeYul::AnimNotify_Step()
{
	UE_LOG(LogTemp, Log, TEXT("AnimNotify Step"));

	UAISense_Hearing::ReportNoiseEvent(GetWorld(),
		TryGetPawnOwner()->GetActorLocation(),
		150.f,
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0),
		1500.f,
		FName(TEXT("Noise")));

	OnStep.Broadcast();
}

void UAnimInstance_LeeYul::AnimNotify_SaveSnapshot()
{
	FName SnapShotPose = TEXT("DeadSnapShot");
	AnimationStopped = true;
	SavePoseSnapshot(SnapShotPose);
}