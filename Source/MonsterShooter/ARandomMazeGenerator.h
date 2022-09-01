// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARandomMazeGenerator.generated.h"

UCLASS()
class MONSTERSHOOTER_API AARandomMazeGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AARandomMazeGenerator();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Maze Settings")
		TSubclassOf<class AMazeCell> CellToSwapClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		int32 ColumnNumber = 8;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		int32 RowNumber = 9;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		float DistanceXBetweenCells = 500;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		float DistanceYBetweenCells = 500;
	//actor spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawnActor")
		TSubclassOf<class AActor> enemyBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawnActor")
		TSubclassOf<class AActor> doorBlueprint;

protected:

	virtual void BeginPlay() override;


private:

	AMazeCell* CellArr[100][100];
	int32 visited[100][100];
	int32 X_Value[4] = { 1,-1,0,0 };
	int32 Y_Value[4] = { 0,0,-1,1 };



private:
	void InitMap();
	void DFS(int X, int Y);
	void SpawnEnemy(FVector location, int32 act);


};

USTRUCT(Atomic)
struct FXYContainer
{
	GENERATED_BODY()
public:
	int x;
	int y;
};
