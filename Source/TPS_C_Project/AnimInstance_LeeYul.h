// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPS_C_ProjectCharacter.h"
#include "AnimInstance_LeeYul.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnStep);

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UAnimInstance_LeeYul : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimInstance_LeeYul();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boolean, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boolean, Meta = (AllowPrivateAccess = true))
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boolean, Meta = (AllowPrivateAccess = true))
	bool AnimationStopped;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	ATPS_C_ProjectCharacter* PlayerRef;

	FOnStep OnStep;

	UFUNCTION()
	void AnimNotify_Step();

	UFUNCTION()
	void AnimNotify_SaveSnapshot();
};
