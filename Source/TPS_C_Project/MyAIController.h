// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MasterChara_Monster.h"
#include <Perception/AIPerceptionComponent.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Uobject/ConstructorHelpers.h>
#include "TPS_C_ProjectCharacter.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;
	virtual FRotator GetControlRotation() const override;
	UBlackboardData* get_Blcakboard() { return BB; }

	//자신에 대한 포인터를 저장하는 변수
	AMasterChara_Monster* Monster;

	//플레이어에 대한 주솟값을 저장하는 변수
	ATPS_C_ProjectCharacter* Player;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	//가시거리
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AISightAge = 15.0f;

	//시야상실거리
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AILoseSightRadius = AISightRadius + 50.0f;

	//시야각
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIFOV = 90.0f;

	//청각 감지 거리
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIHearingRange = 1500.0f;

	//청각자극 수명
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIHearingAge = 5.0f;

	//시야설정 오브젝트
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;
	
	//청각설정 오브젝트
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UAISenseConfig_Hearing* HearingConfig;

	//블랙보드 컴포넌트
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UBlackboardData* BB;

	//비헤이비어트리 <변수>
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	//플레이어와의 거리
	float DistanceToPlayer = 0.0f;

	//자극의 정보를 가지고있는 info, Stimulus구조체 선언
	FActorPerceptionBlueprintInfo info;
	FAIStimulus stim;
};
