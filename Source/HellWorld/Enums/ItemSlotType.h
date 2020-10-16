#pragma once

#include "CoreMinimal.h"
#include "ItemSlotType.generated.h"

UENUM(BlueprintType)
enum class EItemSlotType : uint8
{
	IS_Vicinity			UMETA(DisplayName = "VicinitySlot"),
	IS_Inventory		UMETA(DisplayName = "InventorySlot")
};
