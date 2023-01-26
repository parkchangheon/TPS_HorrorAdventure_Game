// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogStruct.generated.h"
/**
 * 
 */
class TPS_C_PROJECT_API DialogStruct
{
public:
	DialogStruct();
	~DialogStruct();
};

USTRUCT(Atomic, BlueprintType)
struct FDialoginfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Soundfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextDialog;
};

USTRUCT(Atomic, BlueprintType)
struct FDialog : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialoginfo Dialoginfo;

};