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
	if (OtherActor->ActorHasTag("NPC_Moon"))   // 문창섭 패널 앞에 있을때
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
			//여기에 이율 조작+타이머 카운트 넣는다.
			//answer;
			
			UE_LOG(LogTemp, Warning, TEXT("Both Overlap!!"));

			//interact 작동시
			

			//for (int i = 0; i < 4; i++) { // 4번의 패널 조작으로 4번의 for문을 돌려줌

			//	//타이머는 3초 돌아야하는데, 패널을 조작하는 시간을 설정해줘야하므로, 4초로 설정
			//	//3초 끝나고 1초 pause 하는데, 만약 입력이 제대로 되었다면, continue를, 아니라면 다시 interact

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

	//델리게이트 해제과정
	Fuc_DeleSingle.Unbind(); // 정확히는 메모리 해제 함수. 해당 델리게이트에 바인드된 함수를 제거

}



bool AS2R_Second_Lever::FPress()
{
	return true;
}