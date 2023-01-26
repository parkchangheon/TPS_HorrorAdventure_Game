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
	//GetAllActorsOfClass명령어를 사용하기 위한 Subclass선언
	TSubclassOf<AMasterChara_Monster> TSC;

	//GetAllActorsOfClass명령어에서 찾은 액터에대한 배열
	TArray<AActor*> Monsters;

	//액터의 컨트롤러를 사용하기 위한 컨트롤러 변수 선언
	AMasterChara_Monster* ACM;
	AMyAIController* con;

	virtual void Tick(float DeltaTime) override;

	//오버랩 함수 오버라이딩
	UFUNCTION()
	void OnBoxcompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxcompEndOverlap( UPrimitiveComponent* OverlappedComp,  AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
