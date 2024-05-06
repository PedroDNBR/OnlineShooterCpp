#include "Flag.h"
#include "OnlineShooterCpp/Character/BlasterCharacter.h"
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

void AFlag::ResetFlag()
{
	ABlasterCharacter* FlagBearer = Cast<ABlasterCharacter>(GetOwner());
	if (FlagBearer)
	{
		FlagBearer->SetHoldingTheFlag(false);
		FlagBearer->SetOverlappingWeapon(nullptr);
		FlagBearer->UnCrouch();
	}

	if (!HasAuthority()) return;

	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	FlagPole->DetachFromComponent(DetachRules);

	SetWeaponState(EWeaponState::EWS_Initial);

	GetAreaSphere()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetAreaSphere()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	SetOwner(nullptr);
	BlasterOwnerCharacter = nullptr;
	BlasterOwnerController = nullptr;

	SetActorTransform(InitialTransform);
}

void AFlag::OnEquipped()
{
	ShowPickupWidget(false);
	GetAreaSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FlagPole->SetSimulatePhysics(false);
	FlagPole->SetEnableGravity(false);
	FlagPole->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FlagPole->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
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

void AFlag::BeginPlay()
{
	Super::BeginPlay();
	InitialTransform = GetActorTransform();
}
