// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LevelPaddle.generated.h"

class UPrimitiveComponent;
class UCapsuleComponent;
class ALevelSphere;


UENUM(BlueprintType)
enum class PaddleState : uint8 {
  NORMAL UMETA(DisplayName = "Normal"),
  EXTENDED UMETA(DisplayName = "Extended"),
  LONG UMETA(DisplayName = "Long"),
  LASER UMETA(DisplayName = "Laser")
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

  void Accelerate();
  void MoveX(float AxisValue);
  void Fire1(bool bPressed);
  void Fire2(bool bPressed);
  FVector2D GetLastMovement() { return LastMovement; }
private:
  FVector2D RawMovementInput;

  FVector2D LastMovement;
};

UCLASS()
class BLOCKBREAKER_API ALevelPaddle : public APawn
{
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ALevelPaddle();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  FORCEINLINE const FPaddleInput& GetCurrentInput() const { return PaddleInput; }
protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  /** Input binding to move the Paddle left and right on the screen */
  void MoveX(float AxisValue);

  /** Input for special action commands, such as firing lasers, catching a ball, etc. */
  void Fire1Pressed();
  void Fire1Released();
  void Fire2Pressed();
  void Fire2Released();

  /** The component that handles all incoming input to the paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Input")
    FPaddleInput PaddleInput;
  /** How fast the paddle moves from one side of the screen to the other */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Input")
    float MoveSpeed;
  /** The upper and lower limit on the paddle's acceleration as an Absolute value */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Input")
    float MaxAcceleration;
  /** Rate at which speed increases or decreases */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Input")
    float Acceleration;
  /** Static mesh collision component */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    class UCapsuleComponent *CollisionCapsule;
  /** Static mesh collision component */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    class UStaticMeshComponent *PaddleMesh;
  /** The Player controller for the player paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    APlayerController *PaddleController;
  /** The Current state of the player paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    PaddleState PaddleState;
  /** A reference to the active sphere currently in play */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paddle|Other")
    ALevelSphere *ActiveSphere;

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
private:
  /** If the ball falls out of bounds, set this to trigger an animation change */
  UPROPERTY(VisibleAnywhere, Category = "Paddle|Other", meta = (AllowPrivateAccess = "true"))
    uint32 bAlive : 1;

  uint8 bHitWall : 1;

  /** A counter for debug purposes */
  float DebugCounter;
};