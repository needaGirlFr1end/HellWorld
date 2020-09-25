#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ּ� �ε�
	LoadAsset();

	// ���Ǵ� ������Ʈ �ʱ�ȭ
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

