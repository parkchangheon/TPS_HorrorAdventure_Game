// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Master_NPC.h"
#include "Math/TransformNonVectorized.h"
#include "BTT_CameraMove.generated.h"


/**
 * 
 */

UENUM(BlueprintType)
enum class InterpObject : uint8
{
	NPC = 0   UMETA(DisplayName = "NPC"),	//! DisplayName은 언리얼 에디터, 블루프린트에서 표시되는 이름입니다.
	Player			UMETA(DisplayName = "Player")
};

UENUM(BlueprintType)
enum class VectorSelection : uint8
{
	ConversationVector1 = 0   UMETA(DisplayName = "ConversationVector1"),	//! DisplayName은 언리얼 에디터, 블루프린트에서 표시되는 이름입니다.
	ConversationVector2			UMETA(DisplayName = "ConversationVector2"),
	ConversationVector3	 UMETA(DisplayName = "ConversationVector3")
};

UCLASS()
class TPS_C_PROJECT_API UBTT_CameraMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Custom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	VectorSelection VectorToSelect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	InterpObject ObjectToSelect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform CustomTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AMaster_NPC* ObjectToInterp;


public:
	UBTT_CameraMove(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:


};
