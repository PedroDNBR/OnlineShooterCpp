// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayerSessionsSubsystem.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		check(Subsystem);

		if (NumberOfPlayers == Subsystem->DesiredNumOfPublicConnections)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				bUseSeamlessTravel = true;

				FString MatchType = Subsystem->DesiredMatchType;
				if (MatchType == "FreeForAll")
				{
					World->ServerTravel(FString("/Game/Maps/FreeForAll?listen"));
				}
				else if (MatchType == "Teams")
				{
					World->ServerTravel(FString("/Game/Maps/Teams?listen"));
				}
				else if (MatchType == "CaptureTheFlag")
				{
					World->ServerTravel(FString("/Game/Maps/CaptureTheFlag?listen"));
				}

			}
		}
	}

	
}

void ALobbyGameMode::ForceStartMatch()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		check(Subsystem);

		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;

			FString MatchType = Subsystem->DesiredMatchType;
			if (MatchType == "FreeForAll")
			{
				World->ServerTravel(FString("/Game/Maps/FreeForAll?listen"));
			}
			else if (MatchType == "Teams")
			{
				World->ServerTravel(FString("/Game/Maps/Teams?listen"));
			}
			else if (MatchType == "CaptureTheFlag")
			{
				World->ServerTravel(FString("/Game/Maps/CaptureTheFlag?listen"));
			}
			else
			{
				World->ServerTravel(FString("/Game/Maps/FreeForAll?listen"));
			}
		}
	}
}
