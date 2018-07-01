#pragma once

#include "CoreMinimal.h"
#include "Blockbreaker.h"
#include "GameFramework/Actor.h"
#include "LevelArch.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class USoundCue;

UCLASS()
class BLOCKBREAKER_API ALevelArch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelArch();

  /* The Mesh for the Arch */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    UStaticMeshComponent* Mesh;

  /** The Audio component for the Arch */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    UAudioComponent* AudioComponent;

  /** The sound to play when the Arch is hit */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    USoundCue* HitSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
  void PlayHitSound();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  /** Function called whenever the paddle collides with another actor */
  UFUNCTION(BlueprintNativeEvent)
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  void OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
