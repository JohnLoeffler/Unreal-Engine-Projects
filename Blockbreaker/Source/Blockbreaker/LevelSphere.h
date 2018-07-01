#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blockbreaker.h"
#include "LevelSphere.generated.h"

UENUM(BlueprintType)
enum class ESphereState : uint8 {
  NORMAL UMETA (DisplayName = "Normal"),
  MULTISPHERE UMETA (DisplayName = "Multisphere"),
  HARDBALL UMETA(DisplayName = "Hardball"),
  DRILL UMETA(DisplayName = "Drill"),
  BUZZSAW UMETA(DisplayName = "Buzzsaw")
};

UCLASS()
class BLOCKBREAKER_API ALevelSphere : public AActor
{
  GENERATED_BODY()

protected:

      //                        //
      //  Class data fields     //
      //                        //

  /** Indicates how much damage the sphere will cause a brick */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sphere|Data")
    float Damage;

  /** The active state of the sphere */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Data")
    ESphereState State;

  /** Flag for when the sphere has hit the ground and is undergoing its deflation animation */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Status")
    bool bDeflating;

  /** An Array of the texture material assets used by the Sphere */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Assets")
    TArray<UMaterialInstanceDynamic*> MaterialInstances;

  /***/
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    FVector LastPosition;


  

      //                        //
      //  Class Components      //
      //                        //
  /** The Static Mesh Component for the Sphere */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Components")
    UStaticMeshComponent *MeshComponent;
  
  /** The Movement Component for the Sphere */
  
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sphere|Components")
    UProjectileMovementComponent *SphereMovement;
  
      //                        //
      //  Gameplay References   //
      //                        //

  /** Reference to the Player Paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Environmental Reference")
    ALevelPaddle* PlayerPaddle;

  /** Reference to the Player Paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Environmental Reference")
    ABlockbreakerGameModeBase* GameMode;

      //                        //
      //  Cached Assets         //
      //                        //

          /* Mesh Assets    */
  /** A Cached reference to the default sphere mesh asset */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere|Assets|Meshes")
    UStaticMesh* DefaultMesh;
  
          
public:

      //                        //
      //  Public Methods        //
      //                        //      

  /** 
  * Gets the amount of Base Damage the Sphere causes 
  * @return A float with the amount of damage
  */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Status")
    float GetSphereDamage() { return Damage; }

  /**
  *  
  * 
  */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Status")
    void Reset();
  /*
  UFUNCTION(BlueprintImplementableEvent, Category = "Sphere|Status")
    void ResetMovementComponent();
  */


  /**
  * Gets the Current State of the Sphere
  * @return The spheres current ESphereState
  */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Status")
    ESphereState GetSphereState() { return State; }

  /* Member Methods */
  /** Object default constructor */
  ALevelSphere();

  /** Toggles the Ball between actively in play and not */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Status")
    void ToggleActive();

  /** 
  * Checks whether the Ball is in play or not 
  * @return True if the Sphere is active, False otherwise 
  */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Status")
    bool IsInPlay() { return this->bInPlay; }

  /** Sets the balls position if it is not currently active */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Setup")
    void SetSpherePosition(float DeltaMovement);

  /** Gets the projectile Movement component for the sphere */
  
  UFUNCTION(BlueprintCallable, Category = "Sphere|Setup")
    FORCEINLINE UProjectileMovementComponent* GetMovementComponent() { return SphereMovement; }
  
  /** Gets the current location of the sphere */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Setup")
    FORCEINLINE FVector GetSphereLocation() { return GetActorLocation(); }

  /** Sets the Player Paddle for the level */
  UFUNCTION(BlueprintCallable, Category = "Sphere|Setup")
    FORCEINLINE bool SetPlayerPaddle(ALevelPaddle* Paddle) { UE_LOG(LogTemp, Warning, TEXT("Player Paddle Set")); this->PlayerPaddle = Paddle; return true; }

      //                        //
      //  Blueprint Native      //
      //      Events            //
      //                        //
  /** Function for handling hit events */
  UFUNCTION(BlueprintCallable)
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  
  
protected:
  /** Called once when the actor is spawned */
  virtual void BeginPlay() override;

  /** Called every frame  */
  virtual void Tick(float DeltaTime) override;

  /** Called Immediately after construction */
  virtual bool Init();
  /** Called when the Sphere hits the ground */
  virtual void InitSphereDeaden();
private:
  /** Whether the Sphere is actively in play */
  UPROPERTY(VisibleAnywhere)
    uint32 bInPlay : 1;
  /*  Generic debug timer */
  float DefaultTimer;

  FTimerHandle DeflateTimerHandle;
};