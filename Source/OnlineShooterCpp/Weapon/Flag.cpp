#include "Flag.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"

AFlag::AFlag()
{
	FlagPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPole"));
	SetRootComponent(FlagPole);
	GetAreaSphere()->SetupAttachment(FlagPole);
	GetPickupWidget()->SetupAttachment(FlagPole);
	FlagPole->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FlagPole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FlagMesh = CreateDefaultSubobject <USkeletalMeshComponent> (TEXT("FlagMesh"));
	FlagMesh->SetupAttachment(FlagPole);
	FlagMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FlagMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
