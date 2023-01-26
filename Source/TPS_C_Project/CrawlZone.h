// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include "TPS_C_ProjectCharacter.h"
#include "CrawlZone.generated.h"

UCLASS()
class TPS_C_PROJECT_API ACrawlZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrawlZone();

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Boxcomp;

	ATPS_C_ProjectCharacter* PlayerCast;

	//타이머 핸들러용 변수, 일정 틱마다 함수를 발동시켜주기 위해 선언
	FTimerHandle BeginOverlapHandle;
	FTimerHandle EndOverlapHandle;

	FLatentActionInfo LatentInfo;

	FRotator CameraRot;
	//오버랩 함수 오버라이딩
	UFUNCTION(BlueprintNativeEvent)
	void OnBoxcompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnBoxcompBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
		void OnBoxcompEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		virtual void OnBoxcompEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BeginOverlapTimerFunc();

	UFUNCTION()
	void EndOverlapTimerFunc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
