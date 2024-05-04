#include "ElimAnnouncement.h"
#include "Components/TextBlock.h"

void UElimAnnouncement::SetElimAnnouncementText(FString AttackerName, FString VictimName)
{
	if (AnnouncementText)
	{
		FString ElimAnnouncementText = FString::Printf(TEXT("%s elimned %s!"), *AttackerName, *VictimName);
		AnnouncementText->SetText(FText::FromString(ElimAnnouncementText));
	}
}
