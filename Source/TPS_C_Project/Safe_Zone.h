// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterChara_Monster.h"
#include "MyAIController.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include "Safe_Zone.generated.h"


UCLASS()
class TPS_C_PROJECT_API ASafe_Zone : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ASafe_Zone();
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Boxcomp;
	//GetAllActorsOfClass��ɾ ����ϱ� ���� Subclass����
	TSubclassOf<AMasterChara_Monster> TSC;

	//GetAllActorsOfClass��ɾ�� ã�� ���Ϳ����� �迭
	TArray<AActor*> Monsters;

	//������ ��Ʈ�ѷ��� ����ϱ� ���� ��Ʈ�ѷ� ���� ����
	AMasterChara_Monster* ACM;
	AMyAIController* con;

	virtual void Tick(float DeltaTime) override;

	//������ �Լ� �������̵�
	UFUNCTION()
	void OnBoxcompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxcompEndOverlap( UPrimitiveComponent* OverlappedComp,  AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
