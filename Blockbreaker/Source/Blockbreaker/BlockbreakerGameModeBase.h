// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Blockbreaker.h"
#include "BlockbreakerGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8 {
  STARTINGUP,
  RESETTING,
  PLAYING,
  PAUSED,
  ROUNDWON,
  ROUNDLOSS,
  ROUNDSUMMARY,
  UPGRADING,
  GAMELOSS,
  EXITING
};

UCLASS()
class BLOCKBREAKER_API ABlockbreakerGameModeBase : public AGameModeBase
{
  GENERATED_BODY()
protected:
  

  //                    //
  //  GAME STATE DATA   //
  //                    //

  /** The Current game state of the game mode */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    EGameState State;

  /** Whether the Game is currently paused */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bGamePaused;
  
  /** Flag indicating that the level must be reset for the next match */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bRestarting;

  /** Flag indicating that Game Over has beed triggered */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bGameOver;

  /** Flag indicating that Game Exit has been triggered */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bQuit;
  
  /** Flag indicating Victory condition satisfied */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bVictory;

  /** Flag indicating Defeat condition satisfied */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    bool bDefeated;

  //                  //
  //  LEVEL DATA      //
  //                  //

  /** The current level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    int32 LevelNumber;

  /** The current level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    int32 BricksInLevel;

  /** Whether the Grid has been initialized or not */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    uint32 bGridInitialized : 1;
  
  /** The current player score */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|Management|Round Data")
    int32 Score;

  /** The number of player lives */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    int32 PlayerLives;

  /** The Time it took the player to beat the current level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    float Time;

  /** The Difficulty of the Gameplay */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Settings")
    EGameDifficulty Difficulty;

  /** The countdown for the beginning of the round */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Settings")
    float RoundCountdownTime;

  /** The Scoring threshold for Gold Level Acheivement */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Acheivements")
    int32 GoldScore;

  /** The Scoring threshold for Silver Level Acheivement */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Acheivements")
    int32 SilverScore;

  /** The Scoring threshold for Bronze Level Acheivement */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Acheivements")
    int32 BronzeScore;

  /** The Starting Location for the Paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    FVector PaddleLocation;

  /***/
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    TArray<ALevelSphere*> SpheresPendingDeletion;

  /** The current amount of ammo for the Paddle's special weapon */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
    int32 Ammo;

  /**  */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|Management|Round Data|Round Summary")
    int32 TimeBonusValue;

  /**  */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|Management|Round Data|Round Summary")
    int32 LivesBonusValue;

  /**  */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|Management|Round Data|Round Summary")
    int32 AmmoBonusValue;

  /** The Starting Location for the Sphere */
  //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Round Data")
  //  FVector SphereLocation;

  //                      //
  //  OBJECT REFERENCES   //
  //                      //
  
  /** A TArray of the active Spheres for the level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management")
    TArray<ALevelSphere*> ActiveSpheres;

  /** Cached reference to the player paddle */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Actors")
    ALevelPaddle* Player;

  /** Current UI Element on screen */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|User Interface")
    UUserWidget* CurrentUI;

  //                      //
  //  COMPONENTS          //
  //                      //

  /** The Audio Component for the GameMode */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Components")
    UAudioComponent* SFXComponentOne;

  /** The Audio Component for the GameMode */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Components")
    UAudioComponent* SFXComponentTwo;

  /** The Audio Component for the GameMode */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Components")
    UAudioComponent* MusicComponent;

  //                      //
  //  ASSET REFERENCES    //
  //                      //

  /** The Music Asset for the current level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* LevelMusicOne;

  /** The Music Asset played during the countdown to round start */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* IntroMusicOne;

  /** The Music Asset played when the player losses a round */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* OutroMusicOne;

  /** The Music Asset for the current level */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* LevelMusicTwo;

  /** The Music Asset played during the countdown to round start */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* IntroMusicTwo;

  /** The Music Asset played when the player losses a round */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* OutroMusicTwo;

  /** The Music Asset played during level summary after player wins the round */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* VictoryMusic;

  /** The Music Asset played during the Game Over Screen */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Management|Music")
    USoundCue* GameOverMusic;
  

  FTimerHandle StartUpTimer, EndRoundTimer;
  
  virtual void Tick(float DeltaTime) override;

  virtual void BeginPlay() override;

  virtual bool Init();

public:

  /** Default Constructor */
  ABlockbreakerGameModeBase();
  
  /** Destructor */
  virtual ~ABlockbreakerGameModeBase() {}

  /** 
  * Sets the difficulty for the level 
  * @param Dif The EGameDifficulty for the current round 
  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Settings")
    void SetCurrentDifficulty(EGameDifficulty Dif){this->Difficulty = Dif;}
  /** Sets the currently displayed UI element */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Settings")
    void SetCurrentUI(UUserWidget* UI){this->CurrentUI = UI;}
  /** Sets the current game state for the game mode */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void SetGameState(EGameState St){State = St;}
 /**
  * Gets the Difficulty for the Match 
  * @return The EGameDifficulty value for the current round
  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    EGameDifficulty GetCurrentDifficulty(){return this->Difficulty;}
  /**
  * Gets the Gamestate for the Match
  * @return The Gamestate of the current round
  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    EGameState GetGameState(){return this->State;}
  /** 
  * Use to notify the GameMode of Brick destruction and how much it should
  *   adjust the score
  * @param Points The number of points awarded upon brick destruction
  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void NotifyBrickDeath(int32 Points);
  /**
  * Caches a reference to the active player paddle
  * @param Paddle The player paddle
  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Setup")
    void SetPlayerPaddle(ALevelPaddle* Paddle){this->Player = Paddle;}
  /** Adds a sphere to the current count of active spheres in the level */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void AddSphere(ALevelSphere* Sphere); 
  /** Deletes a sphere from the level and initiates match loss if spheres == 0 */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void DeleteSphere(ALevelSphere* Sphere);
  /** Toggles whether the Grid has been initialized */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Setup")
    void ReportBuildSuccess(int32 BrickTotal){UE_LOG(LogTemp, Warning, TEXT("%d bricks in the level according to GameModeBase"), BrickTotal); BricksInLevel = BrickTotal; bGridInitialized = true;}
  /** Checks whether the grid has been initialized */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Setup")
    bool IsGridInitialized(){return bGridInitialized;}
  
  /** Triggers a level reset */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Setup")
    void TriggerReset();
  
  /** Trigger a pause in the gameplay */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerPause();
  
  /** Triggers the game to resume */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerResume();

  /** Triggers Active Play */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerActivePlay();

  /** Triggers the game over event */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerGameOver();

  /** Triggers the game exit event */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerGameExit();

  /** Notifies the GameMode of a Victory condition */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerVictoryCondition();

  /** Notifies the GameMode of a Defeat condition */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void TriggerDefeatCondition();

  //                                  //
  //    GAME STATE PROCESS FUNCTIONS  //
  //                                  //

  /** Checks for changes in the game state */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void CheckGameState(float DeltaTime);

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessExit();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessStartUp();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessReset();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessPlaying();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessPaused();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessRoundWon();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessRoundLoss();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay|Management")
    void ProcessRoundSummary(float DeltaTime);

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessUpgrading();

  /** Processes the Main Menu Action */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Management")
    void ProcessGameLoss();

  //                                  //
  //    BROADCASTERS AND SUBSCRIBER   //
  //                                  //

  bool BroadcastPause(){return bGamePaused;}

  //                                  //
  //    UI UPDATE FUNCTIONS           //
  //                                  //

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 ScoreBonus;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 FinalScore;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 TimeRemaining;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 DisplayedPoints;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 Lives;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 AmmoRemaining;

  //////////////////////////////////////////////////////////
  //
  //  PRIVATE WORKING VARIABLES TO CALCULATE UI UPDATE DATA
  //
  //////////////////////////////////////////////////////////

private:
  float MenuCountdownTimer;
  float TimeRemainingTimer;
  float LivesRemainingTimer;
  float AmmoRemainingTimer;
  float ScoreUpdateTimer;
  float FinalScoreUpdateTimer;
    
  int32 TimeRemainingCounter;
  int32 LivesRemainingCounter;
  int32 AmmoRemainingCounter;
  int32 ScoreUpdateCounter;
  int32 FinalScoreUpdateCounter;

  ///////////////////////////////////////////////////////////
public:
  /**  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Setup")
    int32 Countdown();
  /**  */
  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateRoundTime(float DeltaTime);

  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateCountdownTime(float DeltaTime);

  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateScore(float DeltaTime, int32 PointTotal);

  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateFinalScore(float DeltaTime, int32 PointTotal);

  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateLives(float DeltaTime);

  UFUNCTION(BlueprintCallable, Category = "Gameplay|Update")
    int32 UpdateAmmo(float DeltaTime);

};
