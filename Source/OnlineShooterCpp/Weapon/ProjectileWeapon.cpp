#include "ProjectileWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget, const FVector_NetQuantize& StartLocation, FRotator TargetRotation)
{
    Super::Fire(HitTarget, StartLocation, TargetRotation);

    if (!HasAuthority()) return;

    APawn* InstigatorPawn = Cast<APawn>(GetOwner());
    const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
    if (MuzzleFlashSocket)
    {
        if (ProjectileClass && InstigatorPawn)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = GetOwner();
            SpawnParams.Instigator = InstigatorPawn;

            UWorld* World = GetWorld();
            if (World)
            {
                World->SpawnActor<AProjectile>(
                    ProjectileClass,
                    StartLocation,
                    TargetRotation,
                    SpawnParams
                );
            }
        }
    }
}