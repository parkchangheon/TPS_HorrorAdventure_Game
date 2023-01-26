// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterChara_Monster.h"
#include "Monster_Monster1.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnJumpAttacked)
DECLARE_MULTICAST_DELEGATE(FOnTackleAttacked)
DECLARE_MULTICAST_DELEGATE(FOnGrabEnd)

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AMonster_Monster1 : public AMasterChara_Monster
{
public:
	GENERATED_BODY()
	AMonster_Monster1();
	void SargentJump();
	void EndSargant();
	void Tackle();
	void EndTackle();
	void Grap();

	UFUNCTION()
	void EndGrab();
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	void SetCollisionToIgnoreMonster(bool branch);
	void SetBodyPhysics(bool newbool);
	void UpdateBoneLocation();
	void ResetPlayer();
public:
	FTimerHandle MoveTimer;
	FTimerHandle GrabTimer;
	FOnJumpAttacked JumpAttacked;
	FOnTackleAttacked TackleAttacked;
	FOnGrabEnd GrabEnd;
	FVector Destination;
	TArray<FHitResult> HitResult;
	FHitResult TempResult;
	ACharacter* PlayerCharacter;
	float delta=0;
	float deltaheight;
	float deltaX;
	float deltaY;
	float TimeToJump=1;
	float Height_Constant;
	bool CanSargant=false;
	bool CanTackle = false;
private:
	UAnimBlueprint* Monster1_AnimBP;

};
