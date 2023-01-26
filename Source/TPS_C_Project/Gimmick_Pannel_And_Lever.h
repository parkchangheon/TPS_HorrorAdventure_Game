// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick_Master.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "DoorWidget.h"
#include "PannelWidget.h"
#include "TPS_C_ProjectCharacter.h"
#include "Gimmick_Pannel_And_Lever.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AGimmick_Pannel_And_Lever : public AGimmick_Master
{
	GENERATED_BODY()
private:
	//������ ��� �Լ�
	UFUNCTION()
	void Pannel1_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel2_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel3_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel4_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Lever_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Door_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void StartPannelTimer();
	UFUNCTION()
	void ButtonRequiredEndTimer();
	UFUNCTION()
	bool CheckKey();
	UFUNCTION()
	void ActivateLever();
	UFUNCTION()
	void OpenDoor();

	APlayerController* PlayerController;
	AActor* Player;
	//������ ���� �Լ�
	UFUNCTION()
	void Pannel1_EndOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	AGimmick_Pannel_And_Lever();
	virtual void Interact() override;
	virtual void BeginPlay() override;

	//������ ����
	int32 LastUpdated_Component_Index = -1;
	int32 RemainObject = 4;
	int32 Pw1[4] = { 12,6,9,3 };
	int32 Pw2[4] = { 3,9,6,12 };

	//����ƽ�޽�
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel1;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel2;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel3;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel4;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Lever;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	//�ݸ���
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel1_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel2_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel3_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel4_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Lever_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Door_Collision;

	//bool
	bool Pannel1_IsActivated = false;
	bool Pannel2_IsActivated = false;
	bool Pannel3_IsActivated = false;
	bool Pannel4_IsActivated = false;
	bool Lever_IsActivated = false;
	bool Door_IsActivated = false;
	bool Activated[5] = { false ,false ,false ,false ,false };

	//����
	UPROPERTY(EditAnyWhere)
	TSubclassOf<UDoorWidget> WidgetClass1;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<UPannelWidget> WidgetClass2;

	UDoorWidget* DoorWidgetRef;
	UPannelWidget* PannelWidgetRef;

	//Ÿ�̸� �ڵ鷯
	FTimerHandle WholeTimerHanlder;
	FTimerHandle SwitchTimerHandler;
	FTimerHandle SetRelativeLocationHandler;
	FTimerHandle Delay;
	
};
