#include "GameManager.h"
#include "MovingActor.h"
#include "Kismet/GameplayStatics.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	FMath::RandInit(FDateTime::Now().GetTicks());

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AGameManager::SpawnPlatform,
		6.0f,
		true
	);
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManager::SpawnPlatform()
{
	if (PlatformClass.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlatformClass array is empty!"));
		return;
	}

	FVector BaseLocation = GetActorLocation();

	FVector SpawnLocation;
	bool bValidLocation = false;
	int32 TryCount = 0;


	while (!bValidLocation && TryCount < 20)
	{
		float RandomX = FMath::RandRange(-1000.0f, 1000.0f);
		float RandomY = FMath::RandRange(-1000.0f, 1000.0f);

		SpawnLocation = BaseLocation + FVector(RandomX, RandomY, 0.0f);

		bValidLocation = true;

		for (const FVector& Loc : SpawnedLocations)
		{
			if (FVector::Dist(Loc, SpawnLocation) < 400.0f)
			{
				bValidLocation = false;
				break;
			}
		}

		TryCount++;
	}

	if (!bValidLocation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find valid spawn location"));
		return;
	}


	int32 RandomIndex = FMath::RandRange(0, PlatformClass.Num() - 1);
	TSubclassOf<AActor> SelectedClass = PlatformClass[RandomIndex];

	if (SelectedClass)
	{
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			SelectedClass,
			SpawnLocation,
			SpawnRotation
		);

		if (SpawnedActor)
		{
			SpawnedLocations.Add(SpawnLocation);

			
			if (AMovingActor* Moving = Cast<AMovingActor>(SpawnedActor))
			{
		
				Moving->MoveSpeed = FMath::RandRange(100.0f, 400.0f);
				Moving->MaxRange = FMath::RandRange(200.0f, 800.0f);

			
				float Dir = FMath::RandBool() ? 1.0f : -1.0f;
				Moving->MoveDirection = FVector(0.0f, Dir, 0.0f);
			}
		}
	}
}