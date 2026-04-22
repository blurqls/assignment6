#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(RootScene);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootScene);

	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	bIsForward = true;
	
	MoveDirection = MoveDirection.GetSafeNormal();
	
	if (isDisappear)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DisappearTimerHandle,
			this,
			&AMovingActor::HandleDisappear,
			DisappearTime,
			false
		);
	}
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector Offset = CurrentLocation - StartLocation;

	FVector Direction = bLocalSpace
		? GetActorForwardVector()
		: MoveDirection;

	
	float DistanceAlongDirection = FVector::DotProduct(Offset, Direction);

	if (bIsForward)
	{
		if (DistanceAlongDirection >= MaxRange)
		{
			bIsForward = false;
		}
	}
	else
	{
		if (DistanceAlongDirection <= 0.0f)
		{
			bIsForward = true;
		}
	}

	MoveActor(DeltaTime);
}

void AMovingActor::MoveActor(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	FVector Direction = bLocalSpace
		? GetActorForwardVector()
		: MoveDirection;

	if (bIsForward)
	{
		CurrentLocation += Direction * MoveSpeed * DeltaTime;
	}
	else
	{
		CurrentLocation -= Direction * MoveSpeed * DeltaTime;
	}

	SetActorLocation(CurrentLocation, true);
}

void AMovingActor::HandleDisappear()
{
	Destroy();
}
