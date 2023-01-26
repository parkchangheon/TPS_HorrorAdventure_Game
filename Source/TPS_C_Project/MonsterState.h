// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MonsterState.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API UMonsterState : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	enum State {
		Idle,
		Suspect,
		Detected
	};
};
