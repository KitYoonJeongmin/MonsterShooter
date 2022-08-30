// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterShooter_GameMode.h"

#include "Kismet/GameplayStatics.h"

void AMonsterShooter_GameMode::BeginPlay() {
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &AMonsterShooter_GameMode::CountdownTimer, 1.f, true, 1.f);
}

void AMonsterShooter_GameMode::RestartGameplay(bool Won) {
    if (Won) {
        ResetLevel();
    }
    else {
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonsterShooter_GameMode::ResetLevel, 3.f);
    }
}

void AMonsterShooter_GameMode::ResetLevel() {
    UGameplayStatics::OpenLevel(GetWorld(), "Gameplay");
}

void AMonsterShooter_GameMode::CountdownTimer() {
    TimerCount--;

    if (TimerCount == 0) {
        GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
    }
}