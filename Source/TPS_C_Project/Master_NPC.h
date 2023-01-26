// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include <Components/AudioComponent.h>
#include <Runtime/Engine/Classes/Animation/AnimMontage.h>
#include "ConversationManager.h"
#include "Sound/DialogueVoice.h"
#include "Master_NPC.generated.h"

UCLASS()
class TPS_C_PROJECT_API AMaster_NPC : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAudioComponent* Audio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* DeadAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UConversationManager* ConversationManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Dead;

	FTransform CameraTransform1;

	FTransform CameraTransform2;

	FTransform CameraTransform3;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	AMaster_NPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation();

	UFUNCTION(BlueprintCallable)
	virtual	void DeadEvent();


};
