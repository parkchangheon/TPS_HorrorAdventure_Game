// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Second_Lever.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTagsManager.h"
#include "TimerManager.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


AS2R_Second_Lever::AS2R_Second_Lever()
{ 
	PrimaryActorTick.bCanEverTick = false;

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxMesh"));
	NPC_Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>LeverNPC(TEXT("StaticMesh'/Game/MAP_CONTENTS/PCH_Direct12/Lever/SM_Lever.SM_Lever'"));

	if (LeverNPC.Succeeded())
	{
		NPC_Lever->SetStaticMesh(LeverNPC.Object);
	}

	BoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AS2R_Second_Lever::OnBeginOverlap);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AS2R_Second_Lever::OnCharacterOverlap);
	IsMoonStand_Lever = false;
	IsYoolStand_Lever = false;

	//InputComponent->BindKey(EKeys::F,IE_Pressed, this, &AS2R_Second_Lever::FPress);
}


void AS2R_Second_Lever::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.AddDynamic(this, &AS2R_Second_Lever::OnBeginOverlap);
	//OnActorEndOverlap.AddDynamic(this, &AS2R_Second_Lever::OnOverlapEnd);
}

void AS2R_Second_Lever::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{   
	if (OtherActor->ActorHasTag("NPC_Moon"))   // ��â�� �г� �տ� ������
	{
		UE_LOG(LogTemp, Warning, TEXT("MoonOverlapped"));
		IsMoonStand_Lever = true;
	}
	
	
}


void AS2R_Second_Lever::OnCharacterOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FTimerHandle WaitHandle;
	float WaitTime=4.0f;

	if (OtherActor->ActorHasTag("PC"))
	{
		UE_LOG(LogTemp, Warning, TEXT("LEEYOOL"));
		IsYoolStand_Lever = true;

		if (IsMoonStand_Lever && IsYoolStand_Lever)
		{
			//���⿡ ���� ����+Ÿ�̸� ī��Ʈ �ִ´�.
			//answer;
			
			UE_LOG(LogTemp, Warning, TEXT("Both Overlap!!"));

			//interact �۵���
			

			//for (int i = 0; i < 4; i++) { // 4���� �г� �������� 4���� for���� ������

			//	//Ÿ�̸Ӵ� 3�� ���ƾ��ϴµ�, �г��� �����ϴ� �ð��� ����������ϹǷ�, 4�ʷ� ����
			//	//3�� ������ 1�� pause �ϴµ�, ���� �Է��� ����� �Ǿ��ٸ�, continue��, �ƴ϶�� �ٽ� interact

			//	
			//}
		}

	}
}









void AS2R_Second_Lever::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsMoonStand_Lever = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit"));
}


void AS2R_Second_Lever::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		IsYoolStand_Lever = false;
		UE_LOG(LogTemp, Warning, TEXT("Exit"));
	}

}




void AS2R_Second_Lever::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	//��������Ʈ ��������
	Fuc_DeleSingle.Unbind(); // ��Ȯ���� �޸� ���� �Լ�. �ش� ��������Ʈ�� ���ε�� �Լ��� ����

}



bool AS2R_Second_Lever::FPress()
{
	return true;
}