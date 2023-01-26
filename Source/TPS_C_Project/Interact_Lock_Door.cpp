// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact_Lock_Door.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "TPS_C_ProjectCharacter.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundBase.h"

AInteract_Lock_Door::AInteract_Lock_Door()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	RootComponent = Door;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorAsset(TEXT("StaticMesh'/Game/Hospital/Meshes/Architecture/Doors/SM_Door.SM_Door'"));

	if (DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
	}

	DoorCurrentRotation = 0.0f;

	IsDoorLocked = true;
	DoorLockSound = true;

}


void AInteract_Lock_Door::BeginPlay()
{
	Super::BeginPlay();
	IsDoorclosed = true;
}



void AInteract_Lock_Door::Interact()
{
	FVector LockDoorLocation = Door->GetComponentLocation(); // ��ġ ��������
	// �� ������ ���� �ֱ�( ������)
	if (DoorLockSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LockDoor, LockDoorLocation, FRotator::ZeroRotator);

		DoorLockSound = false;
		return;
	}


	//ĳ���Ͱ� ���� Ű �̸��� �� �̸��� ���ٸ�, isDoorLocked�� false�� �ȴ�.
	if (!IsDoorLocked)
	{

		if (IsDoorclosed) // ���� ���� ����
		{
			//interact ���ڸ��� ���� �����Բ� �ڵ带 §��.
			//ĳ���� ���� �޾Ƽ� ���� ������ ������ �����ϰ� 
			// ���� ������.
			float dot; // ���� ���� ��ȯ float

			FVector vec;
			FTimerHandle WaitHandle;
			float WaitTime = 5.0f;

			AActor* character = GetWorld()->GetFirstPlayerController()->GetPawn();

			vec = character->GetActorLocation() - GetActorLocation();//GetActorLocation  //
			vec.Normalize(); // ����ȭ�� ���� ���͸� ���
			auto forwardvector = GetActorForwardVector();


			dot = FVector::DotProduct(forwardvector, vec);

			float delta = GetWorld()->DeltaTimeSeconds;
			float yawDelta = 0;
			FQuat QuatRotation;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenDoor, LockDoorLocation, FRotator::ZeroRotator);

			if (dot >= 0)
			{
				yawDelta = -90;
				QuatRotation = FQuat(FRotator(0, yawDelta, 0));
				AddActorWorldRotation(QuatRotation, false, 0, ETeleportType::None);
				UE_LOG(LogTemp, Warning, TEXT("right"));
			}


			else
			{
				yawDelta = 90;
				QuatRotation = FQuat(FRotator(0, yawDelta, 0));
				AddActorWorldRotation(QuatRotation, false, 0, ETeleportType::None);
				UE_LOG(LogTemp, Warning, TEXT("left"));

			}

			// IsDoorclosed = false;
			// yawDelta = -yawDelta;
			// Ÿ�̸ӷ� interact �ѵڿ� 5�ʵڿ� ���� �����Բ� �ڵ� �ۼ�

			IsDoorclosed = false;

			GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					QuatRotation = FQuat(FRotator(0, -yawDelta, 0));
					SetActorRotation(QuatRotation);

					UE_LOG(LogTemp, Warning, TEXT("Door close"));
					IsDoorclosed = true;

				}), WaitTime, false);

		}
	}

}