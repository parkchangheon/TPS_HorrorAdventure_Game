// Fill out your copyright notice in the Description page of Project Settings.


#include "CrawlZone.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "StatComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Core/Public/Math/UnrealMathUtility.h>
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

// Sets default values
ACrawlZone::ACrawlZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Boxcomp;
	

	//�ڽ��� ���� ������ �̺�Ʈ Ȱ��ȭ(�⺻���� true�� �ѵ� Ȥ�ø��� ���ִ� ��찡 ����)
	Boxcomp->SetGenerateOverlapEvents(true);

	//�ڽ� ������Ʈ�� ���� ������ �̺�Ʈ�� �Լ��� ���ε�����
	Boxcomp->OnComponentBeginOverlap.AddDynamic(this, &ACrawlZone::OnBoxcompBeginOverlap);
	Boxcomp->OnComponentEndOverlap.AddDynamic(this, &ACrawlZone::OnBoxcompEndOverlap);


}

void ACrawlZone::OnBoxcompBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCast->InterpCameraCrawl();
	if (Cast<ATPS_C_ProjectCharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		float dot = FVector::DotProduct(this->GetActorForwardVector(), PlayerCast->GetActorForwardVector());

		//�պ��͸� �̿��Ͽ� ��, �ڸ� ����
		if (dot >= 0)
			CameraRot = GetRootComponent()->GetRelativeRotation();
		else
			CameraRot = GetRootComponent()->GetRelativeRotation() - FRotator(0, 180, 0);

		PlayerCast->IsCrawling = true;
		PlayerCast->GetCharacterMovement()->MaxWalkSpeed = PlayerCast->StatComponent->GetCrawlSpeed();
		GetWorld()->GetTimerManager().ClearTimer(EndOverlapHandle);
		GetWorldTimerManager().SetTimer(BeginOverlapHandle, this, &ACrawlZone::BeginOverlapTimerFunc, 0.016f, true);
		
		
	}
}

void ACrawlZone::OnBoxcompEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerCast->InterpCameraNormal();
	if (Cast<ATPS_C_ProjectCharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		PlayerCast->IsCrawling = false;
		PlayerCast->GetCharacterMovement()->MaxWalkSpeed = PlayerCast->StatComponent->GetBaseSpeed();
		GetWorld()->GetTimerManager().ClearTimer(BeginOverlapHandle);
		GetWorldTimerManager().SetTimer(EndOverlapHandle, this, &ACrawlZone::EndOverlapTimerFunc, 0.016f, true);
	}
}

void ACrawlZone::BeginOverlapTimerFunc()
{

	if (FMath::IsNearlyEqual(PlayerCast->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), PlayerCast->CapsuleCrawlScale, 1.0f) == true) {
		GetWorld()->GetTimerManager().ClearTimer(BeginOverlapHandle);
		//UKismetSystemLibrary::PrintString(GetWorld(), "Shirink Complete");
	}

	PlayerCast->GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(PlayerCast->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		PlayerCast->CapsuleCrawlScale,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));

	PlayerCast->GetMesh()->SetRelativeLocation(FMath::VInterpTo(PlayerCast->GetMesh()->GetRelativeLocation(),
		PlayerCast->CrawlingMeshVector,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));

	//�÷��̾��� ī�޶� ��ġ ����
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(FMath::RInterpTo(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation(),
		CameraRot,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		1.0f));
}

void ACrawlZone::EndOverlapTimerFunc()
{
	if (FMath::IsNearlyEqual(PlayerCast->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), PlayerCast->CapsuleHalfScale, 1.0f) == true) {
		GetWorld()->GetTimerManager().ClearTimer(EndOverlapHandle);
		//UKismetSystemLibrary::PrintString(GetWorld(), "Maximize Complete");
	}

	PlayerCast->GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(PlayerCast->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		PlayerCast->CapsuleHalfScale,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));

	PlayerCast->GetMesh()->SetRelativeLocation(FMath::VInterpTo(PlayerCast->GetMesh()->GetRelativeLocation(),
		PlayerCast->BaseLocationVector,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));
}

// Called when the game starts or when spawned
void ACrawlZone::BeginPlay()
{
	PlayerCast = Cast<ATPS_C_ProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

