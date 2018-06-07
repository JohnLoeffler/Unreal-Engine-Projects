#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSphere.generated.h"

class UArrowComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class BLOCKBREAKER_API ALevelSphere : public AActor
{
  GENERATED_BODY()

public:
  /** Indicates how much damage the sphere will cause a brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;

  /* Member Methods */
  /** Object default constructor */
  ALevelSphere();

  /** Toggles the Ball between actively in play and not */
  UFUNCTION()
    void ToggleActive() { this->bInPlay = !this->bInPlay; }
  /** Checks whether the Ball is in play or not */
  UFUNCTION()
    bool IsInPlay() { return this->bInPlay; }
  /** Sets the balls position if it is not currently active */
  UFUNCTION()
    void SetSpherePosition(float DeltaMovement);
  UFUNCTION()
    FORCEINLINE UProjectileMovementComponent* GetMovementComponent() { return SphereMovement; }
  UFUNCTION()
    FORCEINLINE FVector GetSphereLocation() { return GetActorLocation(); }

protected:
  /* Member Methods */
  /** Called once when the actor is spawned */
  virtual void BeginPlay() override;

  /** Called every frame  */
  virtual void Tick(float DeltaTime) override;

  /** Function for handling hit events */
  UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /** The mesh for the ball */
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent *Mesh;
  /** The direction of the sphere */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent *SphereMovement;

  /** The direction of the sphere */
  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //UArrowComponent *BallDirection;

private:
  /** Whether the Sphere is actively in play */
  UPROPERTY(VisibleAnywhere)
    uint32 bInPlay : 1;
};