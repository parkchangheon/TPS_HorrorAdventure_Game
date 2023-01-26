// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterChara_Monster.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/PlayerController.h>
#include "MyAIController.h"

// Sets default values
AMasterChara_Monster::AMasterChara_Monster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));
	AIControllerClass = AMyAIController::StaticClass();
	
}

// Called when the game starts or when spawned
void AMasterChara_Monster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterChara_Monster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
