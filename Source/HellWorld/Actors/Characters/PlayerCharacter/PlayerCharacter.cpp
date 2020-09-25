#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 애셋 로드
	LoadAsset();

	// 사용되는 컴포넌트 초기화
	InitializeComponents();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::InitializeComponents()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
		TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacter/Base/BaseBody.BaseBody'"));
	if (SK_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_BASE.Object);

}

void APlayerCharacter::LoadAsset()
{

}

