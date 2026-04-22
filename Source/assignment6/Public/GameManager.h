#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class ASSIGNMENT6_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<TSubclassOf<AActor>> PlatformClass;


	FTimerHandle SpawnTimerHandle;

	
	UPROPERTY()
	TArray<FVector> SpawnedLocations;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnPlatform();
};