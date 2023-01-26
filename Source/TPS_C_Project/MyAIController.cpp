// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MasterChara_Monster.h"
#include "StatComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include <GameFramework/CharacterMovementComponent.h>



AMyAIController::AMyAIController()
{
	//���� �ʿ��� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PrimaryActorTick.bCanEverTick = false;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));
	StatComponent->SetName(FName(TEXT("Monster1")));
	StatComponent->SetStat(StatComponent->GetName());

	SightConfig->SightRadius = StatComponent->GetSightRadius();
	SightConfig->LoseSightRadius = StatComponent->GetLoseSightRadius();
	SightConfig->PeripheralVisionAngleDegrees = StatComponent->GetFOV();
	SightConfig->SetMaxAge(StatComponent->GetSightAge());

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//��û�Ÿ�, ��������� û���� �ʿ��� ������ �ʱ�ȭ
	HearingConfig->HearingRange = StatComponent->GetHearingRadius();
	HearingConfig->SetMaxAge(StatComponent->GetHearingAge());
	
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//��������� Ȱ��ȭ ��Ŵ
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);



	//������Ʈ�� ������Ʈ���� ã�Ƽ� �������Ʈ�� ����ϴ� ��ɾ�, ������ ��θ� ����ϱ� ������ �ٸ� ������Ʈ���� ������ �ʿ䰡 ����
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MixamoAnimPack/Zombie/BaldZombie/BT_Zombie'/"));
	if (obj.Succeeded()) {btree = obj.Object;}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> obj2(TEXT("Blackboard'/Game/MixamoAnimPack/Zombie/BaldZombie/BB_Zombie'/"));
	if (obj2.Succeeded()) {BB = obj2.Object;}


	if (UseBlackboard(BB, Blackboard))
	{
		if (RunBehaviorTree(btree))
		{
			//TODO
		}

	}
	if (GetBlackboardComponent() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetBlackboardComponent Is Null"));
	}
}

void AMyAIController::BeginPlay() {
	Super::BeginPlay();
	//InitPerception();

}

void AMyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	//UE_LOG(LogTemp, Warning, TEXT("Pawn Was Detected"));
	for (size_t i = 0; DetectedPawns.Num() > i; i++)
	{

		if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) == nullptr) { return; }

		if (DetectedPawns[i] == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
			//UE_LOG(LogTemp, Warning, TEXT("%d"), DistanceToPlayer);
			//�÷��̾� ĳ���͸� �÷��̾��� �ּҿ� ������ ������ �ʱ�ȭ
			Player = Cast<ATPS_C_ProjectCharacter>(DetectedPawns[i]);
			GetPerceptionComponent()->GetActorsPerception(Player, info);
			for (size_t j = 0; j < info.LastSensedStimuli.Num(); ++j)
			{
				stim = info.LastSensedStimuli[j];
			}

			if (DistanceToPlayer < AISightRadius && GetBlackboardComponent()->GetValueAsBool(TEXT("InSafeRoom?")) == false)
			{
				//���ðŸ�, ���ð��� �ȿ� ��� ���� �� �� ó��
				Cast<AMasterChara_Monster>(GetPawn())->GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetRunSpeed();
				GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), uint8(State::Detected));
				//UE_LOG(LogTemp, Warning, TEXT("Pawn Was Detected"));
			}
			else if (AIHearingRange > DistanceToPlayer && (stim.Tag == TEXT("Noise")) && GetBlackboardComponent()->GetValueAsBool(TEXT("InSafeRoom?")) == false)
			{
				//��û�Ÿ��� ���� ���� �� ��ó��
				//����� �Ҹ��� �߻��ڰ� �÷��̾��϶��� �����ϰ� �Ǿ�����
				Cast<AMasterChara_Monster>(GetPawn())->GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetBaseSpeed();
				GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), uint8(State::Suspect));
				GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), stim.StimulusLocation);
				//UE_LOG(LogTemp, Warning, TEXT("Pawn Was SusPected"));
			}


		}
	}
}


void AMyAIController::OnPossess(APawn* pawn) {
	Super::OnPossess(pawn);
	GetBlackboardComponent()->SetValueAsObject(TEXT("SelfActor"), pawn);
}

FRotator AMyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) { return FRotator(); }
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

