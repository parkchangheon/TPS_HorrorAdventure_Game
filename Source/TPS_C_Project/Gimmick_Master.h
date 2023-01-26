// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gimmick.h"
#include "Master_Interact.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include "Gimmick_Master.generated.h"

UCLASS()
class TPS_C_PROJECT_API AGimmick_Master : public AMaster_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimmick_Master();

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	TArray<AGimmick_Master*> Relate_Actor;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	bool canActivated;

	
	virtual void Interact_Gimmick_Call();

	virtual void Interact() override;

};
