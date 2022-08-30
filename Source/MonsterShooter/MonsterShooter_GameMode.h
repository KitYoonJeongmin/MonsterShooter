// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MonsterShooter_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERSHOOTER_API AMonsterShooter_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
    void BeginPlay() override;

    void RestartGameplay(bool Won);

private:
    void ResetLevel();

public:
    UPROPERTY(BlueprintReadOnly)
        int TimerCount = 300;

private:
    FTimerHandle CountDownTimerHandle = FTimerHandle();

    void CountdownTimer();

};
