// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gimmick.h"
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include "StatComponent.h"
#include "Master_NPC.h"
#include "Custum_Enum.h"
#include "TPS_C_ProjectCharacter.generated.h"

UCLASS(config=Game)
class ATPS_C_ProjectCharacter : public AMaster_NPC
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleHalfScale;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleCrawlScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrowching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrawling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool IsPlayingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ISTurnRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ISTurnLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector BaseLocationVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector CrawlingMeshVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector CrawlCameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FRotator CrawlCameraRotation;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	Mantling MantlingEnum;

	FTimerHandle WaitHandle;
	FTimerHandle CrouchHandle;

	float LeftRightVal;
	float UpDownVal;
protected:
	void Attack();
	void MovePlayerTo(float speed);
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Yaw(float Value);
	void Sprint();
	void StopSprint();
	void Custom_Crouch();
	void Crouch_Collision_Setting();
	void Stand();
	void Stand_Collision_Setting();
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void BeginPlay();
	ATPS_C_ProjectCharacter();

	UFUNCTION(BlueprintCallable)
	void Interaction();

	UFUNCTION(BlueprintCallable)
	void InterpCameraCrawl();

	UFUNCTION(BlueprintCallable)
	void InterpCameraNormal();

	UFUNCTION(BlueprintCallable)
	void HandleDamage(float damage);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void SetTurnRightAndLeft(bool RightVal, bool LeftVal);

	UFUNCTION()
	void CallDeleFunc_Single();

	virtual void DeadEvent() override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
private:
	void Zoom_In();
	void Zoom_Out();
	void Zoom_In_TimerFunc();
	void Zoom_Out_TimerFunc();
private:
	UPROPERTY()
	class UMyAnimInstance* AnimInstance;
	FTimerHandle Zoom_In_Handler;
	FTimerHandle Zoom_Out_Handler;
	FTimerHandle CameraHandler;
	FVector Zoom_In_Offset = FVector(130.f, 60.f, 10.f);
};

