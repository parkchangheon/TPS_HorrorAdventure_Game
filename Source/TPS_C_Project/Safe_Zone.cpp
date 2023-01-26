// Fill out your copyright notice in the Description page of Project Settings.


#include "Safe_Zone.h"
#include "TPS_C_ProjectCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ASafe_Zone::ASafe_Zone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//박스 컴포넌트를 생성하고 루트 컴포넌트로 지정
	Boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Boxcomp;

	//박스에 대한 오버랩 이벤트 활성화(기본값이 true긴 한데 혹시몰라서 해주는 경우가 많음)
	Boxcomp->SetGenerateOverlapEvents(true);

	//박스 컴포넌트에 대한 오버랩 이벤트를 함수로 바인딩해줌
	Boxcomp->OnComponentBeginOverlap.AddDynamic(this, &ASafe_Zone::OnBoxcompBeginOverlap);
	Boxcomp->OnComponentEndOverlap.AddDynamic(this, &ASafe_Zone::OnBoxcompEndOverlap);

	
}

// Called when the game starts or when spawned
void ASafe_Zone::BeginPlay()
{
	//섭클래스 초기화
	TSC = AMasterChara_Monster::StaticClass();

	//월드에 있는 모든 몬스터를 가지고 온다, 작업량이 압도적으로 많으므로 시작과 동시에 초기화하고 변수를 참조해야함
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSC, Monsters);

	//2중 형변환(캐스팅)
	if (Monsters.Num() > 0)
	{
		ACM = Cast<AMasterChara_Monster>(Monsters[0]);
		con = Cast<AMyAIController>(ACM->GetController());
	}

}

// Called every frame
void ASafe_Zone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  ASafe_Zone::OnBoxcompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//플레이어가 세이프 존에 들어오면 블랙보드 값을 참으로 바꾸어 못쫒아오게 함
		con->GetBlackboardComponent()->SetValueAsBool(TEXT("InSafeRoom?"),true);
	}
}

void ASafe_Zone::OnBoxcompEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//플레이어가 세이프 존에 나가면 블랙보드 값을 거짓으로 바꾸어 쫒아올 수 있게함
		con->GetBlackboardComponent()->SetValueAsBool(TEXT("InSafeRoom?"), false);
	}
}