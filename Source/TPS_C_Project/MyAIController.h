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

	//�ڽſ� ���� �����͸� �����ϴ� ����
	AMasterChara_Monster* Monster;

	//�÷��̾ ���� �ּڰ��� �����ϴ� ����
	ATPS_C_ProjectCharacter* Player;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	//���ðŸ�
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AISightAge = 15.0f;

	//�þ߻�ǰŸ�
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AILoseSightRadius = AISightRadius + 50.0f;

	//�þ߰�
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIFOV = 90.0f;

	//û�� ���� �Ÿ�
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIHearingRange = 1500.0f;

	//û���ڱ� ����
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	float AIHearingAge = 5.0f;

	//�þ߼��� ������Ʈ
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;
	
	//û������ ������Ʈ
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UAISenseConfig_Hearing* HearingConfig;

	//������ ������Ʈ
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	class UBlackboardData* BB;

	//�����̺��Ʈ�� <����>
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	//�÷��̾���� �Ÿ�
	float DistanceToPlayer = 0.0f;

	//�ڱ��� ������ �������ִ� info, Stimulus����ü ����
	FActorPerceptionBlueprintInfo info;
	FAIStimulus stim;
};
