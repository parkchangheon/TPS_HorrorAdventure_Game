// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gimmick.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_C_PROJECT_API UGimmick : public UActorComponent
{
	GENERATED_BODY()
public:
	UGimmick();
	void Interact_With_Key();
	UPROPERTY(BlueprintReadOnly)
	AActor* LastUsuableActor;
	
};