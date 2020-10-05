// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_None			UMETA(DisplayName = None),
	IT_Gear			UMETA(DisplayName = Gear),
	IT_Top			UMETA(DisplayName = Top),
	IT_Bottom		UMETA(DisplayName = Bottom),
	IT_Backpack		UMETA(DisplayName = Backpack),
	IT_Weapon		UMETA(DisplayName = Weapon),
	IT_Consumption	UMETA(DisplayName = Consumption),
	IT_Other		UMETA(DisplayName = Other)
};
