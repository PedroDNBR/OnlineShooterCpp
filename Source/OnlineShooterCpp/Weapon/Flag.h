// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Flag.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESHOOTERCPP_API AFlag : public AWeapon
{
	GENERATED_BODY()
public:
	AFlag();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlagPole;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *FlagMesh;
	
};
