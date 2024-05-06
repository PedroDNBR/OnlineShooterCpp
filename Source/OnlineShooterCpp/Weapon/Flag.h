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
	virtual void Dropped() override;
	void ResetFlag();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlagPole;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *FlagMesh;
	
protected:
	virtual void OnEquipped() override;
	virtual void OnDropped() override;
	virtual void BeginPlay() override;

	FTransform InitialTransform;

public:
	FORCEINLINE FTransform GetInitialTransform() const { return InitialTransform; }

};
