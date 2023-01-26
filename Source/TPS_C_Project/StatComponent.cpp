// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "GehennaGameInstance.h"
#include <Kismet/GamePlayStatics.h>

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UStatComponent::SetStat(FName NewName)
{
	auto MyGameInstance = Cast<UGehennaGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(NewName);
		if (StatData)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetStat Work Was Successful"));
			SetHp(StatData->MaxHp);
			MaxHp = StatData->MaxHp;
			Attack = StatData->Attack;
			BaseSpeed = StatData->BaseSpeed;
			RunSpeed = StatData->RunSpeed;
			CrawlSpeed = StatData->CrawlSpeed;
			CrouchSpeed = StatData->CrouchSpeed;
			SightRadius = StatData->SightRadius;
			LoseSightRadius = StatData->LoseSightRadius;
			SightAge = StatData->SightAge;
			HearingRange = StatData->HearingRange;
			HearingAge = StatData->HearingAge;
			FOV = StatData->FOV;
		}
	}
}

void UStatComponent::SetName(FName NewName)
{
	Name = NewName;
}

void UStatComponent::OnAttacked(float Damage)
{
	int32 NewHp = Hp - Damage;
	SetHp(NewHp);

	//UE_LOG(LogTemp, Warning, TEXT("MyStatComponent's On Attacked Function Was Called"));
}

void UStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
		Hp = 0;

	OnHpChanged.Broadcast();
}

void UStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetStat(Name);
}
