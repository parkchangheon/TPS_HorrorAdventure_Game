// Fill out your copyright notice in the Description page of Project Settings.


#include "Waypoint.h"
#include "TPS_C_ProjectCharacter.h"
#include "MasterChara_Monster.h"
#include "MyAIController.h"

// Sets default values
AWaypoint::AWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnPlayerEnter);
	//BoxComponent->SetCollisionObjectType()

}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaypoint::OnPlayerEnter(UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	AMasterChara_Monster* Monster = nullptr;


	if (OtherActor != nullptr) {
		Monster = Cast<AMasterChara_Monster>(OtherActor);
		if (Monster != nullptr)
		{
			Monster->NextWaypoint = NextWayPoint;
			AMyAIController* con = Cast<AMyAIController>(Monster->GetController());
			con->GetBlackboardComponent()->SetValueAsVector("WayPoint", Monster->NextWaypoint->GetActorLocation());
		}
	}
}

