// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class Mantling : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Jump  UMETA(DisplayName = "Jump"),
	Low_Mantle UMETA(DisplayName = "Low_Mantle"),
	Hight_Mantle UMETA(DisplayName = "Hight_Mantle")
};



class TPS_C_PROJECT_API Custum_Enum
{
public:
	Custum_Enum();
	~Custum_Enum();
};
