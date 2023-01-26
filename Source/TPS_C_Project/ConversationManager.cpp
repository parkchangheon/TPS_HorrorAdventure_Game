// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"
#include "DialogStruct.h"
#include "UObject/ConstructorHelpers.h"
#include "Master_NPC.h"

// Sets default values for this component's properties
UConversationManager::UConversationManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("DataTable'/Game/Data/Dialog/sample.sample'"));
	
	if (DataTable.Succeeded()){DialogTable = DataTable.Object;}



}


// Called when the game starts
void UConversationManager::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


FString UConversationManager::PlayDialog(FName Text)
{
	if (GetOwner()->IsHidden() || DialogTable == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Null"));  return TEXT("ERROR In Conversation Manager Component Function"); }
	FDialoginfo* TableRow = DialogTable->FindRow<FDialoginfo>(Text, "");
	AMaster_NPC* OwnerRef = Cast<AMaster_NPC>(GetOwner());
	if (TableRow->Montage != nullptr) { OwnerRef->PlayAnimMontage(TableRow->Montage); }
	OwnerRef->Audio->SetSound(TableRow->Soundfile);
	OwnerRef->Audio->Play();

	return TableRow->Text;
}

