// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCell.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"


AMazeCell::AMazeCell()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootComponent);

	Wall_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_0"));
	Wall_0->SetupAttachment(RootComponent);

	Wall_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_1"));
	Wall_1->SetupAttachment(RootComponent);

	Wall_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_2"));
	Wall_2->SetupAttachment(RootComponent);

	Wall_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_3"));
	Wall_3->SetupAttachment(RootComponent);

	DebugText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugText"));
	DebugText->SetupAttachment(RootScene);
	DebugText->Text = FText::FromString("");

	PrimaryActorTick.bCanEverTick = false;
}


void AMazeCell::BeginPlay()
{
	Super::BeginPlay();

	NumberWallsUp = 4;
	bCreated = false;

	Floor->SetVisibility(true, true);
	Wall_0->SetVisibility(false, true);
	Wall_1->SetVisibility(true, true);
	Wall_2->SetVisibility(true, true);
	Wall_3->SetVisibility(false, true);

	Wall_0->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Wall_3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMazeCell::Initialize(int32 Row, int32 Column, int32 Index)
{
	bCreated = false;

	RowIndex = Row;
	ColumnIndex = Column;

	NumberWallsUp = 4;

	if (DebugText != nullptr)
	{
		FString Text = FString::FromInt(Index) + " = (" + FString::FromInt(RowIndex) + "," + FString::FromInt(ColumnIndex) + ")";
		DebugText->SetText(FText::FromString(Text));
	}
}

void AMazeCell::HideFloor()
{
	Floor->SetVisibility(false, true);
}

void AMazeCell::ShowFloor()
{
	Floor->SetVisibility(true, true);
}

void AMazeCell::ShowWall(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->SetVisibility(true, true); // Front Wall (ToTop) 
		Wall_0->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case 1:
		Wall_1->SetVisibility(true, true); // Back wall (ToDown)
		Wall_1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case 2:
		Wall_2->SetVisibility(true, true); // Left wall (ToLeft)
		Wall_2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case 3:
		Wall_3->SetVisibility(true, true); // Right wall (ToRight)
		Wall_3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	}
}

void AMazeCell::HideWall(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->DestroyComponent(); // Front Wall (ToTop) 
		break;
	case 1:
		Wall_1->DestroyComponent(); // Back wall (ToDown)
		break;
	case 2:
		Wall_2->DestroyComponent(); // Left wall (ToLeft)
		break;
	case 3:
		Wall_3->DestroyComponent(); // Right wall (ToRight)
		break;
	}
}


void AMazeCell::CreatePassage(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->SetVisibility(false, true); // Front Wall (ToTop) 
		NumberWallsUp -= 1;
		break;
	case 1:
		Wall_1->SetVisibility(false, true); // Back wall (ToDown)
		NumberWallsUp -= 1;
		break;
	case 2:
		Wall_2->SetVisibility(false, true); // Left wall (ToLeft)
		NumberWallsUp -= 1;
		break;
	case 3:
		Wall_3->SetVisibility(false, true); // Right wall (ToRight)
		NumberWallsUp -= 1;
		break;
	}
}

