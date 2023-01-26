// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/SkeletalMeshComponent.h>
#include "MasterChara_Monster.generated.h"

UENUM(BlueprintType)
enum class State : uint8
{
	Idle = 0   UMETA(DisplayName = "Idle"),	//! DisplayName은 언리얼 에디터, 블루프린트에서 표시되는 이름입니다.
	Suspect			UMETA(DisplayName = "Suspect"),
	Detected		UMETA(DisplayName = "Detected")
};


UCLASS()
class TPS_C_PROJECT_API AMasterChara_Monster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMasterChara_Monster();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	int Speed;
	unsigned short Avg_Speed;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	State MonsterState = State::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* NextWaypoint;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;
};
