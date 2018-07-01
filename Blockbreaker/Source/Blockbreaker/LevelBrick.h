#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blockbreaker.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LevelBrick.generated.h"

/** 
* An Enum of the different brick types
*/


UENUM(BlueprintType)
enum class EBrickType : uint8 {
  STANDARD UMETA(DisplayName = "Standard"),
  HARDENED UMETA(DisplayName = "Hardened"),
  REINFORCED UMETA(DisplayName = "Reinforced"),
  BOMB UMETA(DisplayName = "Bomb"),
  EMPTY UMETA(DisplayName = "Empty Space")
};


/**
* An Enum of the different Special types
*/

UENUM(BlueprintType)
enum class ESpecialType : uint8 {
  FIREBOMB UMETA(DisplayName = "FireBomb"),
  ELECTROBOMB UMETA(DisplayName = "Electro Bomb"),
  ACIDPOT UMETA(DisplayName = "Acid Pot"),
  INDESTRUCTIBLE UMETA(DisplayName = "Indestructible"),
  VICTORYBLOCK UMETA(DisplayName = "Victory Block!")
};

/**
* Base class for all blockbreaker bricks, does not include powerups
*/
UCLASS()
class BLOCKBREAKER_API ALevelBrick : public AActor {
  GENERATED_BODY()
protected:

  //                        //
  //  Class data fields     //
  //                        //

  /** A number that identifies the brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    int32 BrickNumber;

  /** A number that identifies the brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    EBrickType BrickType;

  /** The amount of damage the brick can withstand */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    float BaseHealth;

  /** A flag indicating that the brick has recently by damaged by a waveform */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    bool bRecentlyDamaged;

  /** A measure of the bricks ability to withstand indirect damage */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    float Resistance;
  /** Flags whether this brick is immune from damage and cannot pass damage on*/
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    bool bImpervious;

  /** Records the total number of accumulated Points earned causing damaging to brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Data")
    int32 Points;


  //                        //
  //  Class Components      //
  //                        //

  /** The static mesh component for the brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Components")
    UStaticMeshComponent* Mesh;

  /** The static mesh component for the brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Components")
    UAudioComponent* AudioComponent;

  //                        //
  //  Gameplay References   //
  //                        //

  /** A Reference to the GameMode for the level, used to update score, manage indirect damage */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|References")
    ABlockbreakerGameModeBase* GameMode;
public:
  /** A Reference to the LevelBrick above this one */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|References")
    ALevelBrick* AboveBrick;

  /** A Reference to the LevelBrick to the left of this one */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|References")
    ALevelBrick* LeftBrick;

  /** A Reference to the LevelBrick below this one */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|References")
    ALevelBrick* BelowBrick;

  /** A Reference to the LevelBrick to the right of this one */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|References")
    ALevelBrick* RightBrick;
protected:
  //                        //
  //  Cached Assets         //
  //                        //

  /* Mesh Assets    */

  /** A Cached Reference to the Mesh Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    UStaticMesh* StandardMeshAsset;

  /** A Cached Reference to the Mesh Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    UStaticMesh* HardenedMeshAsset;

  /** A Cached Reference to the Mesh Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    UStaticMesh* ReinforcedMeshAsset;

  /** A Cached Reference to the Mesh Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    UStaticMesh* BombMeshAsset;

  /** An Array of the texture material assets used by the brick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    TArray<class UMaterialInstanceDynamic*> MaterialInstances;

  /* Audio Assets   */
  /** A Cached Reference to the Sound Cue Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* HitSound;

  /** A Cached Reference to the Sound Cue Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* BreakSound;

  /** A Cached Reference to the Sound Cue Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* ReinforcedBreakSound;

  /** A Cached Reference to the Sound Cue Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* BombSound;

  /** A Cached Reference to the Sound Cue Asset being used by this LevelBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* DestroyedSound;

  /** Damages the brick by the indicated amount, once resistance factored in */
  UFUNCTION(BlueprintCallable, Category = "Brick|Actions")
    void DamageBrick(float Damage);
public:

  virtual void Tick(float DeltaTime);

  virtual void BeginPlay();

  //                        //
  //  Public Methods        //
  //                        //      
  /** Default Constructor */
  ALevelBrick();

  /** Virtual Destructor */
  virtual ~ALevelBrick();

  /** Sets the Brick Type for the Brick */
  UFUNCTION(BlueprintCallable, Category = "Brick|Gameplay")
    void SetBrickType(EBrickType Type);
  /** Sets the Brick Type for the Brick */
  UFUNCTION(BlueprintCallable, Category = "Brick|Gameplay")
    EBrickType GetBrickType();
  
  /** Use to set the color to apply to the brick texture */
  UFUNCTION(BlueprintCallable, Category = "Brick|Setup")
    void SetBrickNumber(int32 Num);
  /** Use to set the color to apply to the brick texture */
  UFUNCTION(BlueprintCallable, Category = "Brick|Setup")
    void SetGameModeRef(AGameModeBase* Ref);
  /** Use to set the color to apply to the brick texture */
  UFUNCTION(BlueprintCallable, Category = "Brick|Setup")
    void SetBrickColor(FVector Color);
  /** Sets up preloaded assets as soon as the brick is spawned into the world */
  UFUNCTION(BlueprintCallable, Category = "Brick|Setup")
   virtual bool Init();
  /** Registers a hit on the brick by radial damage */
  UFUNCTION(BlueprintCallable, Category = "Brick|Actions")
    void HitWithWaveform(float Force, float TimerDelay);
  
  //                        //
  //  Blueprint Native      //
  //      Events            //
  //                        //
  /** Function called whenever the paddle collides with another actor */
  UFUNCTION(BlueprintNativeEvent)
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  void OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};