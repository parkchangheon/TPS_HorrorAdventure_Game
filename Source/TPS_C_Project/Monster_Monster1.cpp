// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Monster1.h"
#include "StatComponent.h"
#include "MyAIController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/LevelSequence/Public/LevelSequencePlayer.h>


AMonster_Monster1::AMonster_Monster1()
{
	AIControllerClass = AMyAIController::StaticClass();
	StatComponent->SetName(FName(TEXT("Monster1")));
	StatComponent->SetStat(StatComponent->GetName());
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.016f;
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Monster")));
	//GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
}

void AMonster_Monster1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CanSargant && !CanTackle)
	{
		float TimeToAir = PI / TimeToJump;

		FVector NewLocation = GetActorLocation();
		deltaheight = (FMath::Sin(TimeToAir * (delta + DeltaSeconds)) - FMath::Sin(TimeToAir * delta));

		NewLocation += FVector(deltaX, deltaY, deltaheight * Height_Constant);
		SetActorLocation(NewLocation, true, &TempResult);

		delta += DeltaSeconds;
		
		if (TempResult.IsValidBlockingHit() || delta > TimeToJump){ EndSargant();}

	}

	if (CanTackle && !CanSargant)
	{
		 FVector NewLocation = FVector(
			 FMath::FInterpTo(GetActorLocation().X, Destination.X,GetWorld()->GetDeltaSeconds(),10.0f),
			 FMath::FInterpTo(GetActorLocation().Y, Destination.Y, GetWorld()->GetDeltaSeconds(), 10.0f),
			 GetActorLocation().Z);

		SetActorLocation(NewLocation, true, &TempResult);


		if (delta > TimeToJump || TempResult.IsValidBlockingHit()) {EndTackle();}
		
		delta += DeltaSeconds;
	}

}

void AMonster_Monster1::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.TickInterval = 0.016f;
	AMyAIController* PawnController = Cast<AMyAIController>(GetController());
	if (PawnController == nullptr) { return; }
	PawnController->GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (NextWaypoint != nullptr)
		PawnController->GetBlackboardComponent()->SetValueAsVector(TEXT("WayPoint"), NextWaypoint->GetActorLocation());
	
	PawnController->GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), uint8(State::Idle));
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AMonster_Monster1::EndSargant()
{

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation();

	bool bresult = GetWorld()->SweepMultiByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(100.0f)
	);
	
	//DrawDebugSphere(
	//	GetWorld(),
	//	StartLocation,
	//	100.0f,
	//	100.f,
	//	FColor::Red,
	//	true);

	if (bresult) {
		for (int i = 0; i < sizeof(HitResult)/sizeof(FHitResult); i++) {
			if (HitResult[i].Actor == PlayerCharacter)
			{
				//TODO(공격성공의 판정)

				break;
			}
		}
	}

	GetCharacterMovement()->GravityScale = 1.f;
	delta = 0;
	CanSargant = false;
	JumpAttacked.Broadcast();
}

void AMonster_Monster1::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetBaseSpeed();
}

void AMonster_Monster1::SargentJump()
{
	if (PlayerCharacter != nullptr) {

		Destination = PlayerCharacter->GetActorLocation();
		//Destination.Z = GetActorLocation().Z;
	}

	deltaX = ((Destination.X - GetActorLocation().X) * (0.016f / TimeToJump));
	deltaY = ((Destination.Y - GetActorLocation().Y) * (0.016f / TimeToJump));
	Height_Constant = 400 * (FVector::Distance(Destination, GetActorLocation()) / 1000);

	//2.계산상의 위치로 점프

	//도움닫기, 언리얼자체 버그 픽스
	SetActorLocation(FVector(
		GetActorLocation().X,
		GetActorLocation().Y,
		GetActorLocation().Z + 60.f)
	);

	GetCharacterMovement()->GravityScale = 0.f;

	CanSargant = true;
}

void AMonster_Monster1::Tackle()
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	deltaX = ((Destination.X - GetActorLocation().X));
	deltaY = ((Destination.Y - GetActorLocation().Y));

	
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) != nullptr) {

		Destination = FVector(
			PlayerCharacter->GetActorLocation().X + deltaX * 0.1,
			PlayerCharacter->GetActorLocation().Y + deltaY * 0.1,
			PlayerCharacter->GetActorLocation().Z
		);
	}

	GetCharacterMovement()->GravityScale = 0.f;

	CanTackle = true;
}

void AMonster_Monster1::EndTackle()
{
	//3.착지 판정시 피격판정 발생-> 플레이어 처리 fail or success

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation();

	SetActorLocation(GetActorLocation());

	bool bresult = GetWorld()->SweepMultiByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(100.0f)
	);

	//DrawDebugSphere(
	//	GetWorld(),
	//	StartLocation,
	//	100.0f,
	//	100.f,
	//	FColor::Red,
	//	true);

	if (bresult) {
		for (int i = 0; i < sizeof(HitResult) / sizeof(FHitResult); i++) {
			if (HitResult[i].Actor == PlayerCharacter)
			{
				//TODO(공격성공의 판정)

				break;
			}
		}
	}

	GetCharacterMovement()->GravityScale = 1.f;
	delta = 0;
	CanTackle = false;
	UE_LOG(LogTemp, Error, TEXT("ClearAndFinishNode %B"),CanTackle);
	TackleAttacked.Broadcast();
}

void AMonster_Monster1::Grap()
{
	if (!PlayerCharacter) { return; }

	PlayerCharacter->DisableInput(Cast<APlayerController>(PlayerCharacter->GetController()));
	
	PlayerCharacter->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld,true),
		FName(TEXT("r_hand")));

	Monster1_AnimBP = GetMesh()->AnimationBlueprint_DEPRECATED;
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationCustomMode);
	
	SetCollisionToIgnoreMonster(true);
	SetBodyPhysics(true);
	GetWorld()->GetTimerManager().SetTimer(GrabTimer,this,&AMonster_Monster1::UpdateBoneLocation, 0.016f, true);
	PlayerCharacter->GetController()->GetViewTarget();
	Cast<APlayerController>(PlayerCharacter->GetController())->SetViewTarget(this);

	//TODO
	//플레이어를 던지는 애니메이션 등 생동감을 불어넣을 요소
	{
		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		ALevelSequenceActor* SequenceActor;

		FStringAssetReference SequenceName(TEXT("LevelSequence'/Game/GrapAnimation.GrapAnimation'"));
		ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());

		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			Asset,
			PlaybackSettings,
			SequenceActor);

		LevelSequencePlayer->OnFinished.AddDynamic(this, &AMonster_Monster1::EndGrab);
		LevelSequencePlayer->Play();
		
	}
	
}

void AMonster_Monster1::SetCollisionToIgnoreMonster(bool branch)
{
	if (branch)
	{
		PlayerCharacter->GetCharacterMovement()->GravityScale = 0;
		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		PlayerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		//ECC_GameTraceChannel3 = Monster
		//ECC_GameTraceChannel1 = LeeYul

		PlayerCharacter->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
		PlayerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);

		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	}
	else {
		PlayerCharacter->GetCharacterMovement()->GravityScale = 1;
		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		PlayerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		//ECC_GameTraceChannel3 = Monster
		//ECC_GameTraceChannel1 = LeeYul

		PlayerCharacter->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Block);
		PlayerCharacter->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Block);

		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	}

	
}

void AMonster_Monster1::SetBodyPhysics(bool newbool)
{
	PlayerCharacter->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("thigh_l")), newbool,true);
	PlayerCharacter->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("thigh_r")), newbool, true);
	PlayerCharacter->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("clavicle_r")), newbool, true);
	PlayerCharacter->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("clavicle_l")), newbool, true);
}

void AMonster_Monster1::EndGrab()
{
	UE_LOG(LogTemp,Warning,TEXT("EndGrab"))
	if (!PlayerCharacter) { return; }
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	PlayerCharacter->EnableInput(Cast<APlayerController>(PlayerCharacter->GetController()));
	PlayerCharacter->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true));
	SetCollisionToIgnoreMonster(false);
	SetBodyPhysics(false);
	GetWorld()->GetTimerManager().ClearTimer(GrabTimer);
	ResetPlayer();
	GrabEnd.Broadcast();
	Cast<APlayerController>(PlayerCharacter->GetController())->SetViewTarget(PlayerCharacter);
	//나중에 삭제해야할 코드(테스트코드)
	delta = 0;

}

void AMonster_Monster1::UpdateBoneLocation()
{
	FVector SocketLocation = GetMesh()->GetSocketLocation(FName(TEXT("r_hand")));
	PlayerCharacter->GetMesh()->SetWorldLocation(SocketLocation,false,nullptr, ETeleportType::TeleportPhysics);

}

void AMonster_Monster1::ResetPlayer()
{
	//몬스터앞에, 몬스터를 보도록 놔줌
	FVector NewLocation = GetActorForwardVector() * 300.f + GetActorLocation();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		PlayerCharacter->GetActorLocation(),
		GetActorLocation());
	
	PlayerCharacter->SetActorLocation(NewLocation);
	PlayerCharacter->SetActorRotation(FRotator(0.f, NewRotation.Yaw,0.f));
	PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -97.f));
}