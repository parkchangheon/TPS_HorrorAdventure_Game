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
	//각종 필요한 오브젝트를 생성하고 초기화
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

	//가청거리, 감각수명등 청각에 필요한 변수를 초기화
	HearingConfig->HearingRange = StatComponent->GetHearingRadius();
	HearingConfig->SetMaxAge(StatComponent->GetHearingAge());
	
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//감각기관은 활성화 시킴
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);



	//오브젝트를 프로젝트에서 찾아서 블루프린트에 등록하는 명령어, 파일의 경로를 사용하기 때문에 다른 프로젝트에서 수정할 필요가 있음
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
			//플레이어 캐릭터면 플레이어의 주소와 마지막 감각을 초기화
			Player = Cast<ATPS_C_ProjectCharacter>(DetectedPawns[i]);
			GetPerceptionComponent()->GetActorsPerception(Player, info);
			for (size_t j = 0; j < info.LastSensedStimuli.Num(); ++j)
			{
				stim = info.LastSensedStimuli[j];
			}

			if (DistanceToPlayer < AISightRadius && GetBlackboardComponent()->GetValueAsBool(TEXT("InSafeRoom?")) == false)
			{
				//가시거리, 가시각도 안에 들어 왔을 때 논리 처리
				Cast<AMasterChara_Monster>(GetPawn())->GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetRunSpeed();
				GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), uint8(State::Detected));
				//UE_LOG(LogTemp, Warning, TEXT("Pawn Was Detected"));
			}
			else if (AIHearingRange > DistanceToPlayer && (stim.Tag == TEXT("Noise")) && GetBlackboardComponent()->GetValueAsBool(TEXT("InSafeRoom?")) == false)
			{
				//가청거리에 들어와 있을 때 논리처리
				//현재는 소리의 발생자가 플레이어일때만 반응하게 되어있음
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

