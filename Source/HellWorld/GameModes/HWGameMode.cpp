// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameMode.h"
#include "../Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "../Actors/Controllers/PlayerController/TPSPlayerController.h"

AHWGameMode::AHWGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter> TPS_PLAYER_CHARACTER (
		TEXT("Blueprint'/Game/Resources/Blueprints/Characters/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (TPS_PLAYER_CHARACTER.Succeeded())
		DefaultPawnClass = TPS_PLAYER_CHARACTER.Class;

	PlayerControllerClass = ATPSPlayerController::StaticClass();


}