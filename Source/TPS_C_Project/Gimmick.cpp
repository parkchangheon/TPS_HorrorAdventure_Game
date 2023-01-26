// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick.h"
#include "Gimmick_Master.h"

// Sets default values for this component's properties
UGimmick::UGimmick()
{
	PrimaryComponentTick.bCanEverTick = true;
	LastUsuableActor = nullptr;
}


void UGimmick::Interact_With_Key()
{
	
	if (LastUsuableActor == nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Gimmick Component's Ususable Actor Is Null");
		return;
	}
	Cast<AGimmick_Master>(LastUsuableActor)->Interact_Gimmick_Call();
	
}