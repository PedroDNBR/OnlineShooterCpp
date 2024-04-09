#include "ShieldPickup.h"
#include "OnlineShooterCpp/Character/BlasterCharacter.h"
#include "OnlineShooterCpp/BlasterComponents/BuffComponent.h"

void AShieldPickup::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	Super::OnSphereOverlap(
		OverlappedComponent,
		OtherActor,
		OtherComp,
		OtherBodyIndex,
		bFromSweep,
		SweepResult
	);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		UBuffComponent* Buff = BlasterCharacter->GetBuff();
		if (Buff)
		{
			Buff->ReplenishShield(ShieldReplenishAmount, ShieldReplenishTime);
		}
	}

	Destroy();
}
