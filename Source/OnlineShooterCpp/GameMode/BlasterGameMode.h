// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

namespace MatchState
{
	extern ONLINESHOOTERCPP_API const FName Cooldown; // Match duration has been reached. Display winner and begin winner
}

/**
 * 
 */
UCLASS()
class ONLINESHOOTERCPP_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABlasterGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(class ABlasterCharacter* ElimnedCharacter, class ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);
	virtual void RequestRespawn(class ACharacter* ElimnedCharacter, AController* ElimnedController);
	
	UPROPERTY(EditDefaultsOnly);
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly);
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly);
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;

private:
	float CountdownTime = 0.f;

public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }

};
