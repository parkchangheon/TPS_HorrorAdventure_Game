 // Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_C_ProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Gimmick.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Master_Interact.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h >
#include "DrawDebugHelpers.h"
#include "StatComponent.h"
#include "MyAnimInstance.h"
#include "Interactable.h"
#include "Master_NPC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
//////////////////////////////////////////////////////////////////////////
// ATPS_C_ProjectCharacter

ATPS_C_ProjectCharacter::ATPS_C_ProjectCharacter()
{


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	ISTurnLeft = false;
	ISTurnRight = false;
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));
	StatComponent->SetName(FName(TEXT("LeeYul")));
	StatComponent->SetStat(StatComponent->GetName());	

	ConstructorHelpers::FObjectFinder<UAnimMontage>DM(TEXT("AnimMontage'/Game/Project_Gehenna_Leveldesign/Character/Leeyul/LeeYul_Dead.LeeYul_Dead'"));
	DeadAnimMontage = DM.Object;

	
	//UE_LOG(LogTemp, Error, TEXT("%s"), *StatComponent->GetName().ToString());

	//MovePlayerTo(250);
	//FName WeaponSocket(TEXT("hand_r_socket"));  //소켓 만들어준것
	//if (GetMesh()->DoesSocketExist(WeaponSocket))
	//{
	//	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON")); //static컴포넌트 만들어주고
	//	static ConstructorHelpers::FObjectFinder<UStaticMesh>SW(TEXT("StaticMesh'/Game/InfinityBladeWeapons/made/baseballbat.baseballbat'"));
	//	//메쉬로드
	//	if (SW.Succeeded())
	//	{
	//		Weapon->SetStaticMesh(SW.Object);
	//	}
	//	//붙여준다.
	//	Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	//}

	// set our turn rates for input
	{
		BaseTurnRate = 45.f;
		BaseLookUpRate = 45.f;
	}


	//캡슐 콜리전 설정
	{
		CapsuleHalfScale = 96.0f;
		CapsuleCrawlScale = 42.0f;
	}


	//참조용 불린값 설정
	{
		IsCrowching = false;
		IsCrawling = false;
	}

	//위치벡터변수 초기화
	{
		CrawlingMeshVector = GetMesh()->GetRelativeLocation() + FVector(0.0f, 0.0f, -42.0f);
		BaseLocationVector = FVector(0.0f, 0.0f, -97.0f);
	}


	CrawlCameraLocation = FVector(200.0f, -27.0f, -15.0f);
	CrawlCameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
		GetCharacterMovement()->JumpZVelocity = 600.f;
		GetCharacterMovement()->AirControl = 0.2f;
	}

	MantlingEnum = Mantling::Normal;
	

	Tags.Add("PC");
}



void ATPS_C_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPS_C_ProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPS_C_ProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ATPS_C_ProjectCharacter::Yaw);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATPS_C_ProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATPS_C_ProjectCharacter::LookUpAtRate);

	// VR headset functionality
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATPS_C_ProjectCharacter::Interaction);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATPS_C_ProjectCharacter::Attack);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPS_C_ProjectCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPS_C_ProjectCharacter::StopSprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATPS_C_ProjectCharacter::Custom_Crouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATPS_C_ProjectCharacter::Stand);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ATPS_C_ProjectCharacter::Zoom_In);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ATPS_C_ProjectCharacter::Zoom_Out);
}

void ATPS_C_ProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FDele_Single.Bind(this, ATPS_C_ProjectCharacter::CallDeleFunc_Single());

}

void ATPS_C_ProjectCharacter::Interaction()
{
	//라인트레이싱 코드 - 창헌
	FHitResult OutHit;
	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * 400.0f;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName());

		AMaster_Interact* Obj = Cast<AMaster_Interact>(OutHit.Actor);
		if (Obj)
		{
			Obj->Interact();
		}
		else if (OutHit.Actor.Get()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			//TODO
			//interface속 interact함수 호출
			AMaster_NPC* NPC = Cast<AMaster_NPC>(OutHit.Actor);
			NPC->Interact();
		}
	}
	//라인트레이스 시각화
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 1.0f);


	//기존 익재님의 코드
	//Gimmick_Component->Interact_With_Key();
}

void ATPS_C_ProjectCharacter::InterpCameraCrawl()
{
	//마우스 인풋 무력화
	if (!UGameplayStatics::GetPlayerController(GetWorld(), 0)) { return; }
	
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(true);

	//타이머 설정, 타이머를 이용하여 부드럽게 카메라를 이동할 예정
	GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (FollowCamera->GetRelativeLocation() == CrawlCameraLocation && FollowCamera->GetRelativeRotation() == CrawlCameraRotation) {
				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
			//followcamera의 relative위치를 vinterp를 이용하여 옮길 코드
			FollowCamera->SetRelativeLocation(FMath::VInterpTo(
				FollowCamera->GetRelativeLocation(),
				CrawlCameraLocation,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			FollowCamera->SetRelativeRotation(FMath::RInterpTo(
				FollowCamera->GetRelativeRotation(),
				CrawlCameraRotation,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			//cameraboom의 회전치를 초기화 시킴


		}), 0.005f, true);
	
}

void ATPS_C_ProjectCharacter::InterpCameraNormal()
{
	//마우스 인풋 무력화
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetIgnoreLookInput(false);

	//타이머 설정, 타이머를 이용하여 부드럽게 카메라를 이동할 예정
	GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (FollowCamera->GetRelativeLocation() == FVector(0,0,0) && FollowCamera->GetRelativeRotation() == FRotator(0,0,0)) {
				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
			//followcamera의 relative위치를 vinterp를 이용하여 옮길 코드
			FollowCamera->SetRelativeLocation(FMath::VInterpTo(
				FollowCamera->GetRelativeLocation(),
				FVector(0, 0, 0),
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			FollowCamera->SetRelativeRotation(FMath::RInterpTo(
				FollowCamera->GetRelativeRotation(),
				FRotator(0,0,0),
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

		}), 0.005f, true);
}


void ATPS_C_ProjectCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false; 
}

void ATPS_C_ProjectCharacter::SetTurnRightAndLeft(bool RightVal, bool LeftVal)
{
	ISTurnRight = RightVal;
	ISTurnLeft = LeftVal;
	//UE_LOG(LogTemp, Error, TEXT("ISTurnRight: %d,    ISTurnLeft: %d"), ISTurnRight, ISTurnLeft);
}

void ATPS_C_ProjectCharacter::HandleDamage(float damage)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage Hurt"));
	StatComponent->SetHp(StatComponent->GetHp() - damage);
	if (StatComponent->GetHp() <= 0) { DeadEvent(); }
}

void ATPS_C_ProjectCharacter::Zoom_In()
{
	//TODO
	//무기를 들고 있을때에만 가능하도록 조건문을 추가할것
	IsAming = true;
	bUseControllerRotationYaw = true;
	GetWorldTimerManager().ClearTimer(Zoom_Out_Handler);
	GetWorldTimerManager().SetTimer(Zoom_In_Handler, this, &ATPS_C_ProjectCharacter::Zoom_In_TimerFunc, 0.016f, true);

}

void ATPS_C_ProjectCharacter::Zoom_Out()
{
	//TODO
	//무기를 들고 있을때에만 가능하도록 조건문을 추가할것
	IsAming = false;
	bUseControllerRotationYaw = false;
	GetWorldTimerManager().ClearTimer(Zoom_In_Handler);
	GetWorldTimerManager().SetTimer(Zoom_Out_Handler, this, &ATPS_C_ProjectCharacter::Zoom_Out_TimerFunc, 0.016f, true);
}

void ATPS_C_ProjectCharacter::Zoom_In_TimerFunc()
{
	FVector CurrentOffset = GetCameraBoom()->SocketOffset;
	GetCameraBoom()->SocketOffset = FMath::VInterpTo(CurrentOffset, Zoom_In_Offset, GetWorld()->GetDeltaSeconds(), 3.f);
	if ((CurrentOffset - Zoom_In_Offset).IsNearlyZero()){ GetWorldTimerManager().ClearTimer(Zoom_In_Handler); }
}

void ATPS_C_ProjectCharacter::Zoom_Out_TimerFunc()
{
	FVector CurrentOffset = GetCameraBoom()->SocketOffset;
	GetCameraBoom()->SocketOffset = FMath::VInterpTo(CurrentOffset, FVector::ZeroVector, GetWorld()->GetDeltaSeconds(), 3.f);
	if (CurrentOffset.IsNearlyZero()) { GetWorldTimerManager().ClearTimer(Zoom_Out_Handler); }
}

void ATPS_C_ProjectCharacter::Custom_Crouch()
{
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetCrouchSpeed();
	GetWorld()->GetTimerManager().ClearTimer(CrouchHandle);
	GetWorldTimerManager().SetTimer(CrouchHandle, this, &ATPS_C_ProjectCharacter::Crouch_Collision_Setting, 0.016f, true);
}

void ATPS_C_ProjectCharacter::Crouch_Collision_Setting()
{
	if (FMath::IsNearlyEqual(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), CapsuleCrawlScale, 1.0f) == true) {
		GetWorld()->GetTimerManager().ClearTimer(CrouchHandle);
		//UKismetSystemLibrary::PrintString(GetWorld(), "Shirink Complete");
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		CapsuleCrawlScale,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));

	GetMesh()->SetRelativeLocation(FMath::VInterpTo(GetMesh()->GetRelativeLocation(),
		CrawlingMeshVector,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));
}

void ATPS_C_ProjectCharacter::Stand()
{
	
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetBaseSpeed();
	GetWorld()->GetTimerManager().ClearTimer(CrouchHandle);
	GetWorldTimerManager().SetTimer(CrouchHandle, this, &ATPS_C_ProjectCharacter::Stand_Collision_Setting, 0.016f, true);
}

void ATPS_C_ProjectCharacter::Stand_Collision_Setting()
{
	if (FMath::IsNearlyEqual(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), CapsuleHalfScale, 1.0f) == true) {
		GetWorld()->GetTimerManager().ClearTimer(CrouchHandle);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		CapsuleHalfScale,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));

	GetMesh()->SetRelativeLocation(FMath::VInterpTo(GetMesh()->GetRelativeLocation(),
		BaseLocationVector,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		2.0f));
}


void ATPS_C_ProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void ATPS_C_ProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATPS_C_ProjectCharacter::Attack()
{
	//if (IsAttacking)
	//	return;



	//AnimInstance->PlayAttackMontage(0);
	//IsAttacking = true;

	//AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); //animinstance를 찾는다


	//if (AnimInstance)
	//{
	//	AnimInstance->PlayAttackMontage(0);
	//}
	//


	//AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); //animinstance를 찾는다

	//if (AnimInstance)
	//{
	//	AnimInstance->PlayAttackMontage(0);
	//}
}

void ATPS_C_ProjectCharacter::MoveForward(float Value)
{
	UpDownVal = Value;


	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATPS_C_ProjectCharacter::MoveRight(float Value)
{
	
	LeftRightVal = Value;
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATPS_C_ProjectCharacter::Yaw(float Value)
{
	
	AddControllerYawInput(Value);
	
	if (GetVelocity().Size() == 0) {
		//Right
		if (Value > 0.3) {
			SetTurnRightAndLeft(true, false);
		}
		else { ISTurnRight = false; }

		//Left
		if (Value < -0.3) { SetTurnRightAndLeft(false, true); }
		else { ISTurnLeft = false; }

		
	}
	else 
	{
		//UE_LOG(LogTemp, Error, TEXT("Yaw"));
		SetTurnRightAndLeft(false, false);
	}

}

void ATPS_C_ProjectCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetRunSpeed();
}

void ATPS_C_ProjectCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetBaseSpeed();
}

void ATPS_C_ProjectCharacter::MovePlayerTo(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ATPS_C_ProjectCharacter::DeadEvent()
{

	Super::DeadEvent();
	if (DeadAnimMontage->IsValidToPlay()) {
		PlayAnimMontage(DeadAnimMontage);
		CameraBoom->bInheritPitch = false;
		CameraBoom->bInheritYaw = false;
		CameraBoom->bInheritRoll = false;
		GetWorld()->GetTimerManager().SetTimer(CameraHandler, FTimerDelegate::CreateLambda([&]()
			{
				UE_LOG(LogTemp, Warning, TEXT("Timer"));
				CameraBoom->SetRelativeRotation(FMath::RInterpTo(
					CameraBoom->GetRelativeRotation(),
					FRotator(-90.f, 0.f, 0.f),
					GetWorld()->GetDeltaSeconds(),
					1.0f));


				if (FMath::IsNearlyEqual(CameraBoom->GetRelativeRotation().Pitch, -90.f, 1.0f)) {
					GetWorld()->GetTimerManager().ClearTimer(CameraHandler);
				}

			}), 0.01f, true);

	}
	
}

void ATPS_C_ProjectCharacter::CallDeleFunc_Single()
{
	UE_LOG(LogTemp, Warning, TEXT("Just Do it!"));
}