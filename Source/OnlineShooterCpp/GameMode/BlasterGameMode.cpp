// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterGameMode.h"
#include "OnlineShooterCpp/Character/BlasterCharacter.h"
#include "OnlineShooterCpp/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimnedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	if (ElimnedCharacter)
	{
		ElimnedCharacter->Elim();
	}
}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimnedCharacter, AController* ElimnedController)
{
	if (ElimnedCharacter)
	{
		ElimnedCharacter->Reset();
		ElimnedCharacter->Destroy();
	}

	if (ElimnedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimnedController, PlayerStarts[Selection]);
	}

}
