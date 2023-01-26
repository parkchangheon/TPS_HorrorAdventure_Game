// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick_Master.h"
#include "TPS_C_ProjectCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AGimmick_Master::AGimmick_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AGimmick_Master::Interact_Gimmick_Call()
{

}

void AGimmick_Master::Interact()
{
	Interact_Gimmick_Call();
}
