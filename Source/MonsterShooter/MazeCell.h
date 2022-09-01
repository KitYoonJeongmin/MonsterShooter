// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCell.generated.h"

UCLASS()
class MONSTERSHOOTER_API AMazeCell : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Floor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MazeCell")
		class UTextRenderComponent* DebugText;


public:
	// Sets default values for this actor's properties
	AMazeCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	void Initialize(int32 Row, int32 Column, int32 Index);

	FORCEINLINE bool GetIsCreated() { return bCreated; };
	FORCEINLINE void SetIsCreated(bool Value) { bCreated = Value; };

	FORCEINLINE bool AllWallsIntact() { return (NumberWallsUp >= 4); };


	void HideFloor();

	void ShowFloor();

	void ShowWall(int32 WallIndex);

	void HideWall(int32 WallIndex);

	void CreatePassage(int32 WallIndex);


	FORCEINLINE FVector2D GetCoords()
	{
		return FVector2D(ColumnIndex, RowIndex); // X, Y
	}

private:
	bool bCreated;

	int32 ColumnIndex;
	int32 RowIndex;
	int32 NumberWallsUp = 0;

};
