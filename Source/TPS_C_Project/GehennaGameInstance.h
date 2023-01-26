// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "GehennaGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CrawlSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float BaseSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float RunSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CrouchSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float SightRadius;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float SightAge;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float LoseSightRadius;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float FOV;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float HearingRange;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float HearingAge;
};


UCLASS()
class TPS_C_PROJECT_API UGehennaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UDataTable* MyStats;
public:
	UGehennaGameInstance();

	virtual void Init() override;

	FMyCharacterData* GetStatData(FName RowName);
};
