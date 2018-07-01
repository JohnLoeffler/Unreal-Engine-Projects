// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blockbreaker.h"
#include "LevelPaddle.generated.h"

class UPrimitiveComponent;
class UCapsuleComponent;
class USkeletalMesh;
class USkeletalMeshComponent;
class UStaticMesh;
class UStaticMeshComponent;
class ALevelSphere;
class ALevelBumper;
class UAudioComponent;
class USoundCue;
class ABlockbreakerGameModeBase;

UENUM(BlueprintType)
enum class EPaddleState : uint8 {
  NORMAL UMETA(DisplayName = "Normal"),
  EXTENDED UMETA(DisplayName = "Extended"),
  GUNS UMETA(DisplayName = "Guns"),
  LASER UMETA(DisplayName = "Laser"),
  CATCHER UMETA(DisplayName = "Catcher")
};

USTRUCT(BlueprintType)
struct FPaddleInput {
  GENERATED_USTRUCT_BODY()
public:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle|Input")
    FVector2D MovementInput;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle|Input")
    float MaxAcceleration;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle|Input")
    uint32 bFire1 : 1;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle|Input")
    uint32 bFire2 : 1;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle|Input")
    uint32 bPause : 1;

  void Accelerate();
  void MoveX(float AxisValue);
  void Fire1(bool bPressed);
  void Fire2(bool bPressed);
  void Pause(bool bPressed);
  FVector2D GetLastMovement(){ return LastMovement; }
private:
  FVector2D RawMovementInput;

  FVector2D LastMovement;
};

UCLASS()
class BLOCKBREAKER_API ALevelPaddle : public APawn{
  GENERATED_BODY()

public:

  /*
  * Class data fields and base object commands, setters, getters, contructor, etc
  */
      //                    //
      //  Class data fields //
      //                    //

      /** How fast the paddle moves from one side of the screen to the other */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float MoveSpeed;

  /** The upper and lower limit on the paddle's acceleration as an Absolute value */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float MaxAcceleration;

  /** Rate at which speed increases or decreases */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float Acceleration;

  
  /** The cooldown required for the Paddle's projectile weapon */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float WeaponCooldown;
  
  /** The current amount of time the Paddle can exist in an overpowered state before reverting to normal */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float OverpowerTimeLimit;
  
  /** The current amount of time the Paddle can exist in an underpowered state before reverting to normal */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    float UnderpowerTimeLimit;
  
  /** Flag used to trigger an animation change */
  UPROPERTY(VisibleAnywhere, Category = "Paddle|Other")
    uint32 bAlive : 1;

  /** Flags whether the paddle has been paused by the Gamemode. Not the same as Alive, which should only be used for round losses */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    uint32 bReceivingPauseBroadcast : 1;

  /** Flag controlling Paddle's ability to fire */
  UPROPERTY(VisibleAnywhere, Category = "Paddle|Other")
    uint32 bCeasefire : 1;

  /** A counter that the paddle can use for debugging purposes */
  UPROPERTY(VisibleAnywhere, Category = "Paddle|Debugging")
  float DebugCounter;

  /** The Current state of the player paddle; essentially, how is it powered up or powered down */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Attributes")
    EPaddleState PaddleState;

  /** A pause flag telling the GameMode to pause the game, prevents input to the paddle while true, and notifies other actors when to pause action */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Communiques")
    bool bRequestingPause;

protected:

      //                    //
      //  Class Components  //
      //                    //

  /** Input Control Component  */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Components")
    FPaddleInput PaddleInput;
  
  /** Capsule collision component */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Components")
    UCapsuleComponent *CollisionCapsule;
  
  /** Skeletal mesh component for meshes with animation */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Components")
    USkeletalMeshComponent *SkeletalPaddleMesh;
  
  /** Static mesh component */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Components")
    UStaticMeshComponent *StaticPaddleMesh;
  
  /** The Player controller for the player paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Components")
    APlayerController *PaddleController;
  
  /** The Audio component for the Paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Audio")
    UAudioComponent* AudioComponent;

  //
  //  Environment References
  //

  /** A reference to the active spheres currently in play */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Spheres")
    TArray<ALevelSphere*> ActiveSpheres;
  
  /** A reference to the current level's GameMode */
   ABlockbreakerGameModeBase *GameMode;
  
  //
  //  Cached Paddle Assets
  //

      /* Mesh Assets */
  /** The Default Static mesh for the Paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Cached Meshes")
    UStaticMesh* DefaultMesh;
  
  /** The Skeletal mesh for the Paddle in its Extended state */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Cached Meshes")
    UStaticMesh* ExtendedMesh;
  
  /** The Skeletal mesh for the Paddle in its Laser state */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Cached Meshes")
    UStaticMesh* LaserMesh;
  
  /** The Skeletal mesh for the Paddle in its Gun state */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Cached Meshes")
    UStaticMesh* GunsMesh;
  
      /* Audio Assets */

  /** The sound to use when the paddle is hit by the sphere */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Audio")
    USoundCue* HitSound;

public:
  /*
  *
  *
  */

  // Sets default values for this pawn's properties
  ALevelPaddle();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  /** Adds a reference to a currently active sphere */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Setup")
    FORCEINLINE bool AddActiveSphere(ALevelSphere* Sphere) { UE_LOG(LogTemp, Warning, TEXT("Sphere added to Paddle"));  this->ActiveSpheres.Add(Sphere); return true; }

  /** Caches a reference to the currently active sphere */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Setup")
    FORCEINLINE bool DeleteSphere(ALevelSphere* Sphere) {this->ActiveSpheres.Remove(Sphere); return true; }

  /** returns the current paddle location */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Position")
    FORCEINLINE FVector GetPaddlePosition() { return GetActorLocation(); }

  /** Gets the SkeletalMeshComponent */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Components")
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() { return SkeletalPaddleMesh; }

  /** Gets the StaticMeshComponent */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Components")
    FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() { return StaticPaddleMesh; }

  /** Toggles whether the player is "alive" */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Member Data")
    void ToggleAlive(){bAlive = !bAlive;}

  /** Caches the Active GameMode for the Paddle */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Object References")
    void SetGameMode(ABlockbreakerGameModeBase* GM) { UE_LOG(LogTemp, Warning, TEXT("GameMode Set in Player Paddle")); this->GameMode = GM; }


  /** 
  * Switches the current paddle mesh to the cached mesh for the given state 
  * @param State The current EPaddleState of the paddle
  * @return True if successful, False if error
  */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Assets")
    bool SetActiveMesh(EPaddleState State);

  /** Gets a reference to this paddle */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Communication")
    ALevelPaddle* GetPaddleRef(){return this;}

  /** Tells the paddle to play its cached sound for when the sphere hits it */
  UFUNCTION(BlueprintCallable, Category = "Paddle|Actions")
    void PlayHitSound();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

/*
*   Input Functions
*/

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
  /** Gets the current input for the paddle */
  FORCEINLINE const FPaddleInput& GetCurrentInput() const { return PaddleInput; }
protected:
  /** Input binding to move the Paddle left and right on the screen */
  void MoveX(float AxisValue);

  /** Input for special action commands, such as firing laser, catching a ball, etc. */
  void Fire1Pressed();
  /** Calls any functions to be performed upon release of the primary fire input */
  void Fire1Released();
  /** Input for secondary action commands, such as charging the laser, catching a ball, etc. */
  void Fire2Pressed();
  /** Calls any functions to be performed upon release of the secondary fire input */
  void Fire2Released();
  /** Used to signal to the GameMode that the pause command was issued */
  void PausePressed();

/*
*   BLUEPRINT EVENT IMPLEMENTATIONS 
*/

  /** Function called whenever the paddle collides with another actor */
  UFUNCTION(BlueprintNativeEvent)
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  void OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /** Function called whenever the paddle collides with another actor */
  UFUNCTION(BlueprintNativeEvent)
    void OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  void OnOverlapBegin_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  UFUNCTION(BlueprintNativeEvent)
    void OnOverlapEnd(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  void OnOverlapEnd_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};