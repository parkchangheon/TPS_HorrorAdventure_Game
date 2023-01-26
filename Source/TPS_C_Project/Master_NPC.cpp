// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_NPC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values
AMaster_NPC::AMaster_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	ConversationManager = CreateDefaultSubobject<UConversationManager>(TEXT("Conversation Component"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	}

	// Create a follow camera
	{

		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	}

	{
		CameraTransform1 = FTransform(FRotator(0, 240, 0 ), FVector(185, 88, 60), FVector(1, 1, 1));
		CameraTransform2 = FTransform(FRotator(0,180, 0 ), FVector(200, 0, 60), FVector(1, 1, 1));
		CameraTransform3 = FTransform(FRotator(0,20, 0 ), FVector(92, -37, 70), FVector(1, 1, 1));
	
	}

}

// Called when the game starts or when spawned
void AMaster_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaster_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMaster_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMaster_NPC::Interact_Implementation()
{
	
}

void AMaster_NPC::DeadEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("CharacterWasDead"));

	//사망 애니메이션 재생 ->캐릭터마다 다를텐데

	//사망 카메라 애니메이션 재생 ->플레이어 캐릭터용

	//플레이어 컨트롤러 언택트
	Dead = true;
	GetController()->GetPawn()->UnPossessed();
	
	
	//게임오버 위젯 생성

}