// Fill out your copyright notice in the Description page of Project Settings.


#include "Safe_Zone.h"
#include "TPS_C_ProjectCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ASafe_Zone::ASafe_Zone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�ڽ� ������Ʈ�� �����ϰ� ��Ʈ ������Ʈ�� ����
	Boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Boxcomp;

	//�ڽ��� ���� ������ �̺�Ʈ Ȱ��ȭ(�⺻���� true�� �ѵ� Ȥ�ø��� ���ִ� ��찡 ����)
	Boxcomp->SetGenerateOverlapEvents(true);

	//�ڽ� ������Ʈ�� ���� ������ �̺�Ʈ�� �Լ��� ���ε�����
	Boxcomp->OnComponentBeginOverlap.AddDynamic(this, &ASafe_Zone::OnBoxcompBeginOverlap);
	Boxcomp->OnComponentEndOverlap.AddDynamic(this, &ASafe_Zone::OnBoxcompEndOverlap);

	
}

// Called when the game starts or when spawned
void ASafe_Zone::BeginPlay()
{
	//��Ŭ���� �ʱ�ȭ
	TSC = AMasterChara_Monster::StaticClass();

	//���忡 �ִ� ��� ���͸� ������ �´�, �۾����� �е������� �����Ƿ� ���۰� ���ÿ� �ʱ�ȭ�ϰ� ������ �����ؾ���
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSC, Monsters);

	//2�� ����ȯ(ĳ����)
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
		//�÷��̾ ������ ���� ������ ������ ���� ������ �ٲپ� ���i�ƿ��� ��
		con->GetBlackboardComponent()->SetValueAsBool(TEXT("InSafeRoom?"),true);
	}
}

void ASafe_Zone::OnBoxcompEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//�÷��̾ ������ ���� ������ ������ ���� �������� �ٲپ� �i�ƿ� �� �ְ���
		con->GetBlackboardComponent()->SetValueAsBool(TEXT("InSafeRoom?"), false);
	}
}