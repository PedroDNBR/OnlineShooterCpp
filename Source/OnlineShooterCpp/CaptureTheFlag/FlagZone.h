#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnlineShooterCpp/Types/Team.h"
#include "FlagZone.generated.h"

UCLASS()
class ONLINESHOOTERCPP_API AFlagZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlagZone();

	UPROPERTY(EditAnywhere)
	ETeam Team;

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* ZoneSphere;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


protected:
	virtual void BeginPlay() override;

};
