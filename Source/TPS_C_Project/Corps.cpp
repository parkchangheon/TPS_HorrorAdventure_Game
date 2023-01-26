// Fill out your copyright notice in the Description page of Project Settings.


#include "Corps.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACorps::ACorps() {
	SkMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkMesh->SetCollisionProfileName(FName(TEXT("RagDoll")));
	CapsulCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	RootComponent = SkMesh;
	CapsulCollision->SetupAttachment(SkMesh);
	CapsulCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	}

	{
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	}
}

void ACorps::Interact()
{
	Interact_Blueprint_Call();
	
}

