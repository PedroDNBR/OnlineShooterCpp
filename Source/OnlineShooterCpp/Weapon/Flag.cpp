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

void AFlag::Dropped()
{
	SetWeaponState(EWeaponState::EWS_Dropped);
	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	FlagPole->DetachFromComponent(DetachRules);
	SetOwner(nullptr);
	BlasterOwnerCharacter = nullptr;
	BlasterOwnerController = nullptr;
}

void AFlag::OnEquipped()
{
	ShowPickupWidget(false);
	GetAreaSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FlagPole->SetSimulatePhysics(false);
	FlagPole->SetEnableGravity(false);
	FlagPole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFlag::OnDropped()
{
	if (HasAuthority())
	{
		GetAreaSphere()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	FlagPole->SetSimulatePhysics(true);
	FlagPole->SetEnableGravity(true);
	FlagPole->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FlagPole->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	FlagPole->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	FlagPole->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}
