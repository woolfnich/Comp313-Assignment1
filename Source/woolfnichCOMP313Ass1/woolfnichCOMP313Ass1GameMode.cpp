// Copyright Epic Games, Inc. All Rights Reserved.

#include "woolfnichCOMP313Ass1GameMode.h"
#include "woolfnichCOMP313Ass1Character.h"
#include "UObject/ConstructorHelpers.h"

AwoolfnichCOMP313Ass1GameMode::AwoolfnichCOMP313Ass1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
