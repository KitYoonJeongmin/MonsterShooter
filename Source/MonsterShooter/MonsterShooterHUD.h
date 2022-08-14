// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MonsterShooterHUD.generated.h"

UCLASS()
class AMonsterShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMonsterShooterHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

