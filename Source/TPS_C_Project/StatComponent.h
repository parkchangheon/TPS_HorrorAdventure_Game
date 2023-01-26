// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_C_PROJECT_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void OnAttacked(float Damage);
	FName GetName() { return Name; }
	int32 GetAttack() { return Attack; }
	int32 GetHp() { return Hp; }
	float GetHpRatio() { return Hp / (float)MaxHp; }
	int32 GetMaxHp() { return MaxHp; }
	float GetBaseSpeed() { return BaseSpeed; }
	float GetRunSpeed() { return RunSpeed; }
	float GetCrawlSpeed() { return CrawlSpeed; }
	float GetCrouchSpeed() { return CrouchSpeed; }
	float GetSightRadius() { return SightRadius; }
	float GetLoseSightRadius() { return LoseSightRadius; }
	float GetSightAge() { return SightAge; }
	float GetHearingRadius() { return HearingRange; }
	float GetHearingAge() { return HearingAge; }
	float GetFOV() { return FOV; }
	void SetHp(int32 NewHp);
	UFUNCTION(BlueprintCallable)
	void SetStat(FName NewName);
	void SetName(FName NewName);
	virtual void InitializeComponent() override;
private:
	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	FName Name;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CrawlSpeed;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float BaseSpeed;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float RunSpeed;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CrouchSpeed;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float SightRadius;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float LoseSightRadius;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float SightAge;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float HearingRange;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float HearingAge;

	UPROPERTY(EditAnyWhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float FOV;
public:
	FOnHpChanged OnHpChanged;
};
