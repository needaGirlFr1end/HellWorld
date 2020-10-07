#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "VicinityItemDetectorComponent.generated.h"


UCLASS()
class HELLWORLD_API UVicinityItemDetectorComponent : public USphereComponent
{
	GENERATED_BODY()

private :
	// ����� ������ ���͵��� ������ �迭
	TArray<class AWorldItem*> VicinityItems;

public:	
	UVicinityItemDetectorComponent();

protected:
	virtual void BeginPlay() override;

private :
	// ����� �������� �����Ǿ��� ��� ȣ��� �޼���
	UFUNCTION()
	void OnVicinityItemDetected(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
