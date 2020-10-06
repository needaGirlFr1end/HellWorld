
#include "ItemData.h"

FString FItemData::ItemCodeToDataTableKey(FString itemCode)
{
	int32 intItemCode = FCString::Atoi(*itemCode);

	if (1000 <= intItemCode && intItemCode <= 2999)
		return FString(EQUIP);

	return FString(TEXT(""));
}