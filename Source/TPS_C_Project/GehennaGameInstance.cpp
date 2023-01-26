// Fill out your copyright notice in the Description page of Project Settings.


#include "GehennaGameInstance.h"

UGehennaGameInstance::UGehennaGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> Data(TEXT("DataTable'/Game/Data/PawnStat/DT_PawnData.DT_PawnData'"));


	MyStats = Data.Object;

}

void UGehennaGameInstance::Init()
{
	Super::Init();
	//UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"), GetStatData(FName(TEXT("LeeYul")))->CrawlSpeed);
}

FMyCharacterData* UGehennaGameInstance::GetStatData(FName RowName)
{
	return MyStats->FindRow<FMyCharacterData>(RowName, TEXT(""));
}
