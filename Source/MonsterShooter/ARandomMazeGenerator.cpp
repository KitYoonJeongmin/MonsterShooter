// Fill out your copyright notice in the Description page of Project Settings.


#include "ARandomMazeGenerator.h"
#include "Door.h"
#include "Math/UnrealMathUtility.h"
#include "MazeCell.h"


AARandomMazeGenerator::AARandomMazeGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AARandomMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	InitMap();
	DFS(RowNumber, ColumnNumber);

}


void AARandomMazeGenerator::InitMap()
{
	FVector SpawnPosition = GetActorLocation();

	for (int iRow = 0; iRow < RowNumber; ++iRow)
	{
		SpawnPosition.X = GetActorLocation().X;

		for (int iCol = 0; iCol < ColumnNumber; ++iCol)
		{
			// Spawn each cell
			FActorSpawnParameters SpawnParamenters;
			SpawnParamenters.Owner = this;
			//SpawnParamenters.Instigator = Instigator;

			AMazeCell* SpawnedCell = GetWorld()->SpawnActor<AMazeCell>(CellToSwapClass, SpawnPosition, FRotator::ZeroRotator, SpawnParamenters);

			if (SpawnedCell != nullptr)
			{
				// Attach cell to this ator

				SpawnedCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				if (iRow > 3)
					SpawnEnemy(SpawnPosition,0);

				if (iRow == RowNumber - 1)
				{
					SpawnedCell->ShowWall(3);
				}
				else if (iCol == ColumnNumber - 1)
				{
					SpawnedCell->ShowWall(0);
				}
				else if (iRow == 0 && iCol == 0)
				{
					SpawnedCell->HideWall(1);
				}
				int32 CellIndex = iRow * ColumnNumber + iCol;

				SpawnedCell->Initialize(iRow, iCol, CellIndex);

				CellArr[iRow][iCol] = SpawnedCell;
				visited[iRow][iCol] = false;
			}

			SpawnPosition.X += DistanceXBetweenCells;
		}

		SpawnPosition.Y += DistanceYBetweenCells;
	}
	SpawnEnemy(SpawnPosition, 1);
}

void AARandomMazeGenerator::DFS(int X, int Y)
{
	//stack에 넣음
	TArray<FXYContainer> stack;
	FXYContainer currentXY;
	currentXY.x = 0;
	currentXY.y = 0;
	stack.Add(currentXY);
	visited[0][0] = true;
	while (stack.Num() != 0)
	{
		//랜덤 방향으로 이동
		int index = FMath::RandRange(0, 3);
		while (4)
		{
			index = (index + 1) % 4;

			if ((currentXY.x + X_Value[index]) >= 0
				&& X > (currentXY.x + X_Value[index])
				&& (currentXY.y + Y_Value[index]) >= 0
				&& (Y > currentXY.y + Y_Value[index])
				)
			{
				if (visited[currentXY.x + X_Value[index]][currentXY.y + Y_Value[index]] == false)
				{
					switch (index)
					{
					case 0:
						CellArr[currentXY.x + X_Value[index]][currentXY.y + Y_Value[index]]->HideWall(2);
						break;
					case 1:
						CellArr[currentXY.x][currentXY.y]->HideWall(2);
						break;
					case 2:
						CellArr[currentXY.x][currentXY.y]->HideWall(1);
						break;
					case 3:
						CellArr[currentXY.x + X_Value[index]][currentXY.y + Y_Value[index]]->HideWall(1);
						break;
					}

					//위치변경
					currentXY.x += X_Value[index];
					currentXY.y += Y_Value[index];
					visited[currentXY.x][currentXY.y] = true;
					//스택에 넣음
					stack.Add(currentXY);
					break;
				}
			}
			if (index == 3)
			{
				//더이상 갈곳이 없어pop
				stack.Pop();
				if (stack.Num() == 0)
					break;
				int i = stack.Num() - 1;
				currentXY.x = stack[i].x;
				currentXY.y = stack[i].y;
			}
		}
	}


}

void AARandomMazeGenerator::SpawnEnemy(FVector location,int32 act)
{
	int32 Random = FMath::RandRange(1, 5);
	if (act == 1) { Random = 1; }
	if (Random == 1 && enemyBlueprint)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			UE_LOG(LogTemp, Log, TEXT("SpawnEnemy"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			FRotator rotator = FRotator::ZeroRotator;
			location.X += 250.f;
			location.Y -= 250.f;
			location.Z += 100.f;

			//FVector  SpawnLocation = GetActorLocation();
			//SpawnLocation.Z -= 90.0f;

			if (act == 0)
			{
				rotator = FRotator::ZeroRotator;
				location.X += 0.f;
				location.Y -= 0.f;
				location.Z += 10.f;
				world->SpawnActor<AActor>(enemyBlueprint, location, rotator, SpawnParams);
			}
			else if (act == 1)
			{
				rotator = FRotator::ZeroRotator + FRotator(0.f, 90.f, 0.f);
				location.X -= 200.f;
				location.Y -= 535.f;
				location.Z = 0.f;

				world->SpawnActor<AActor>(doorBlueprint, location, rotator, SpawnParams);
			}

		}
	}
}