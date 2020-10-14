#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "VicinityItemDetectorComponent.generated.h"


UCLASS()
class HELLWORLD_API UVicinityItemDetectorComponent : public USphereComponent
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	// Charater Info Widet 객체
	UPROPERTY()
	class UWidgetCharacterInfo * CharacterInfoWidgetInstance;

	// 가까운 아이템 액터들을 저장할 배열
	TArray<class AWorldItem*> VicinityItems;

public:	
	UVicinityItemDetectorComponent();

protected:
	virtual void BeginPlay() override;

private :
	// 가까운 아이템이 감지되었을 경우 호출될 메서드
	UFUNCTION()
	void OnVicinityItemDetected(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnVicinityItemLost(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);


};
