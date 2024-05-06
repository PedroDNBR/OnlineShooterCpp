#include "CaptureTheFlagGameMode.h"
#include "OnlineShooterCpp/Weapon/Flag.h"
#include "OnlineShooterCpp/CaptureTheFlag/FlagZone.h"
#include "OnlineShooterCpp/GameState/BlasterGameState.h"

void ACaptureTheFlagGameMode::PlayerEliminated(ABlasterCharacter* ElimnedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	ABlasterGameMode::PlayerEliminated(ElimnedCharacter, VictimController, AttackerController);
}

void ACaptureTheFlagGameMode::FlagCaptured(AFlag* Flag, AFlagZone* Zone)
{
	bool bValidCapture = Flag->GetTeam() != Zone->Team;
	ABlasterGameState* BGameState = Cast<ABlasterGameState>(GameState);
	if (BGameState)
	{
		if(Zone->Team == ETeam::ET_BlueTeam)
		{
			BGameState->BlueTeamScores();
		}
		if (Zone->Team == ETeam::ET_RedTeam)
		{
			BGameState->RedTeamScores();
		}
	}
}
