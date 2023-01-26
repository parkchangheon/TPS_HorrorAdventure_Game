// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene_6_2_Cabinet.h"

ACutScene_6_2_Cabinet::ACutScene_6_2_Cabinet()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skeletal Mesh"));
	CapsulCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Data1(TEXT("StaticMesh'/Game/Project_Gehenna_Leveldesign/Mesh/Prop/SM_Cabinet_Opened.SM_Cabinet_Opened'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Data2(TEXT("StaticMesh'/Game/Project_Gehenna_Leveldesign/Mesh/Prop/SM_Cabinet_Closed.SM_Cabinet_Closed'"));
	Mesh->SetStaticMesh(Data2.Object);
	OpenedMesh = Data1.Object;
	ClosedMesh = Data2.Object;
	RootComponent = CapsulCollision;
	Mesh->SetupAttachment(CapsulCollision);
	CapsulCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void ACutScene_6_2_Cabinet::Interact()
{
	Interact_Blueprint_Call();

}

void ACutScene_6_2_Cabinet::Open()
{
	if (OpenedMesh == nullptr) { return; }
	Mesh->SetStaticMesh(OpenedMesh);
	IsOpen = true;
}

void ACutScene_6_2_Cabinet::Close()
{
	if (ClosedMesh == nullptr) { return; }
	Mesh->SetStaticMesh(ClosedMesh);
	IsOpen = false;
}
