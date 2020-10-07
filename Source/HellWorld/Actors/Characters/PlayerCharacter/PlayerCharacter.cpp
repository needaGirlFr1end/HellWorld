#include "PlayerCharacter.h"
#include "../../Controllers/PlayerController/TPSPlayerController.h"
#include "../../../AnimInstances/PlayerCharacter/PlayerAnimInstance.h"

#include "../../../Components/VicinityItemDetector/VicinityItemDetectorComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ּ� �ε�
	LoadAsset();

	// ���Ǵ� ������Ʈ �ʱ�ȭ
	InitializeComponents();
}


#pragma region Character Class Override
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerInfo.Initialize();
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationLock();
	UpdateRunState();
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::OnRunKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		this, &APlayerCharacter::OnRunKeyReleased);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::OnJumpKeyPressed);
}


void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<ATPSPlayerController>(NewController);
	bIsControlled = true;
}


void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	PlayerController = nullptr;
	bIsControlled = false;
}
#pragma endregion


#pragma region IPlayerControllable Implement
void APlayerCharacter::OnControllerHorizontalInput(
	FVector worldDirection, float axis)
{
	// ��Ʈ�ѷ� ���� ���� / ���������� �̵���ŵ�ϴ�.
	AddMovementInput(worldDirection, HorizontalInputAxis = axis);

}

void APlayerCharacter::OnControllerVerticalInput(
	FVector worldDirection, float axis)
{
	// ��Ʈ�ѷ� ���� �� / �������� �̵���ŵ�ϴ�.
	AddMovementInput(worldDirection, VerticalInputAxis = axis);
}
#pragma endregion


void APlayerCharacter::InitializeComponents()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
		TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacter/Base/BaseBody.BaseBody'"));
	if (SK_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_BASE.Object);

#pragma region Camera Settings...
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));

	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	// ��Ʈ�ѷ� yaw ȸ���� ���� SpringArm �� ȸ���ϵ��� �մϴ�.
	SpringArm->bUsePawnControlRotation = true;

	// ��Ʈ�ѷ� yaw ȸ���� ���� ĳ���Ͱ� ȸ������ �ʵ��� �մϴ�.
	bUseControllerRotationYaw = false;
#pragma endregion

#pragma region Vicinity ItemDetecter Component Settings...
	VicinityItemDetector = CreateDefaultSubobject<UVicinityItemDetectorComponent>(TEXT("VICINITY_ITEM_DETECTOR"));
	VicinityItemDetector->SetupAttachment(GetRootComponent());
#pragma endregion




#pragma region Animation Settings...
	if (IsValid(PlayerCharacterAnimClass))
	{
		GetMesh()->SetAnimInstanceClass(PlayerCharacterAnimClass);
	}
#pragma endregion


}


void APlayerCharacter::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> PLAYER_ANIM_INSTANCE(
		TEXT("AnimBlueprint'/Game/Resources/Blueprints/Characters/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));
	if (PLAYER_ANIM_INSTANCE.Succeeded())
		PlayerCharacterAnimClass = PLAYER_ANIM_INSTANCE.Class;
	else { UE_LOG(LogTemp, Error, TEXT("PLAYER_ANIM_INSTANCE is not loaded!")); }
}


void APlayerCharacter::RotationLock()
{
	// �������� �ƴ� ��, �̵� Ű�� ���ȴٸ� ĳ���͸� ��Ʈ�ѷ� ȸ�������� 
	// �ε巴�� ȸ����ŵ�ϴ�.
	GetCharacterMovement()->bUseControllerDesiredRotation = 
		IsMoveKeyPressed() && !IsInAir();
}


void APlayerCharacter::UpdateRunState()
{
	// �޸��� ���� ����
	bIsRun = (bRunKeyPressed && VerticalInputAxis > 0.5f);

	// �̵� �ӷ��� �����մϴ�.
	/// - �޸��� ���¶�� ? RunSpeed : WalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = bIsRun ?
		GetPlayerInfo()->RunSpeed : GetPlayerInfo()->WalkSpeed;
}


#pragma region Input Bind

void APlayerCharacter::OnRunKeyPressed()
{
	// �޸��� Ű ���� ���·� ����
	bRunKeyPressed = true;

}

void APlayerCharacter::OnRunKeyReleased()
{
	// �޸��� Ű ������ ���·� ����
	bRunKeyPressed = false;
}

void APlayerCharacter::OnJumpKeyPressed()
{
	// ����
	Jump();
}

#pragma endregion
