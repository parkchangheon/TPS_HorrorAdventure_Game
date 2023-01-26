
#pragma once

#include "CoreMinimal.h"
#include "Master_Interact.h"
#include "Components/CapsuleComponent.h"
#include "CutScene_6_2_Cabinet.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API ACutScene_6_2_Cabinet : public AMaster_Interact
{
	GENERATED_BODY()
public:
	ACutScene_6_2_Cabinet();
	virtual void Interact() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Interact_Blueprint_Call();

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();
	UStaticMeshComponent* GetMesh() { return Mesh; };
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOpen = false;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsulCollision;

	UStaticMesh* OpenedMesh;
	UStaticMesh* ClosedMesh;
	
};
