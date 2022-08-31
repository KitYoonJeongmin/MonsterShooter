// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterShooter_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


void AMonsterShooter_GameMode::BeginPlay() {
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &AMonsterShooter_GameMode::CountdownTimer, 1.f, true, 1.f);
    winWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), winWidget);
    deadWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), deadWidget);
}

void AMonsterShooter_GameMode::RestartGameplay(bool Won) {
    EndingWidget(Won);
    /*
    if (Won) {

        //ResetLevel();
    }
    else {
        //FTimerHandle TimerHandle;
        //GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonsterShooter_GameMode::ResetLevel, 3.0f);
    }*/
}

void AMonsterShooter_GameMode::ResetLevel() {
    UGameplayStatics::OpenLevel(GetWorld(), "TestMap");
}

void AMonsterShooter_GameMode::CountdownTimer() {
    TimerCount--;

    if (TimerCount == 0) {
        GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
    }
}

void AMonsterShooter_GameMode::EndingWidget(bool won)
{
    UGameplayStatics::SetGamePaused(GetWorld(), true);
    if (won)
    {
        if (winWidgetInstance != nullptr)
            winWidgetInstance->AddToViewport();
        
    }
    else
    {
        if (deadWidgetInstance != nullptr)
            deadWidgetInstance->AddToViewport();
    }
    APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
    OurPlayerController->bShowMouseCursor = true;
}
