// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTeleportBox.h"

AMyTeleportBox::AMyTeleportBox() {
	OnActorBeginOverlap.AddDynamic(this, &AMyTeleportBox::EnterTeleporter);
	OnActorEndOverlap.AddDynamic(this, &AMyTeleportBox::ExitTeleporter);
	teleporting = false;

	
}

void AMyTeleportBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTeleportBox::EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor) {
	if (otherActor && otherActor != this)
	{
		if (otherTele) // �ٸ� ��ġ�� �Ҵ��ߴ���.
		{

			//ȭ�� �����Ÿ��� or ������



			//�ڷ���Ʈ�Ѵ�.
			ATPS_C_ProjectCharacter* character = Cast< ATPS_C_ProjectCharacter>(otherActor);
			if (character && !otherTele->teleporting)
			{
				teleporting = true;
				character->SetActorRotation(otherTele->GetActorRotation());
				character->GetController()->SetControlRotation(character->GetActorRotation());
				character->SetActorLocation(otherTele->GetActorLocation());
			}
		}

	}
	



	//�ش� ���� ����
	Destroy();
}

void AMyTeleportBox::ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTele && !teleporting)
		{
			otherTele->teleporting = false;
		}
	}

	//�ش� ���� ����
	Destroy();
}
