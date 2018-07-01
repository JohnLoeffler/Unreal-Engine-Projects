// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BlockbreakerGameModeBase.h"
#include "LevelPaddle.h"
#include "LevelSphere.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaddleController.h"
#include "BlockbreakerGameInstance.h"
#include "../Public/RoundSummaryWidget.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ABlockbreakerGameModeBase::ABlockbreakerGameModeBase(){
  PrimaryActorTick.bCanEverTick = true;
  PrimaryActorTick.SetTickFunctionEnable(true);
  SetActorTickEnabled(true);

  DefaultPawnClass = ALevelPaddle::StaticClass();
  PlayerControllerClass = APaddleController::StaticClass();
  bGridInitialized = false;
  
  PlayerLives= 3;     //Cast<UBlockbreakerGameInstance>(UGameplayStatics::GetGameInstance(this))->PlayerLives;
  Score= 0;           //Cast<UBlockbreakerGameInstance>(UGameplayStatics::GetGameInstance(this))->PlayerScore;
  LevelNumber= 1;
  Difficulty= EGameDifficulty::VERYHARD;  //Cast<UBlockbreakerGameInstance>(UGameplayStatics::GetGameInstance(this))->Difficulty;
  RoundCountdownTime= 5.0;
  Time= 90.0;
  Ammo= 0;

  TimeRemainingCounter = 0;
  LivesRemainingCounter = 0;
  AmmoRemainingCounter = 0;
  ScoreUpdateCounter = 0;
  FinalScoreUpdateCounter = 0;

  BronzeScore= 0;
  SilverScore= 0;
  GoldScore= 0;

  bRestarting = false;
  bVictory = false;
  bDefeated = false;

  MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
  MusicComponent->bAutoActivate = false;
  RootComponent  = MusicComponent;

  SFXComponentOne  = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComponentOne"));
  SFXComponentOne->bAutoActivate = false;
  SFXComponentOne->SetupAttachment(RootComponent);

  SFXComponentTwo = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComponentTwo"));
  SFXComponentTwo->bAutoActivate = false;
  SFXComponentTwo->SetupAttachment(RootComponent);

  static ConstructorHelpers::FObjectFinder<USoundCue> IntroMusicOneCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song01MatchIntro.Song01MatchIntro'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> OutroMusicOneCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song01MatchLoss.Song01MatchLoss'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> LevelMusicOneCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song01MatchLoop.Song01MatchLoop'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> IntroMusicTwoCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song02MatchIntro.Song02MatchIntro'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> OutroMusicTwoCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song02MatchLoss.Song02MatchLoss'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> LevelMusicTwoCue(TEXT("SoundCue'/Game/Assets/Audio/Music/Song02MatchLoopCue.Song02MatchLoopCue'"));
  
  static ConstructorHelpers::FObjectFinder<USoundCue> VictoryMusicCue(TEXT("SoundCue'/Game/Assets/Audio/Music/MatchWinMusic.MatchWinMusic'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> DefeatMusicCue(TEXT("SoundCue'/Game/Assets/Audio/Music/GameOverMusicCue.GameOverMusicCue'"));

  IntroMusicOne = IntroMusicOneCue.Object;
  OutroMusicOne = OutroMusicOneCue.Object;
  LevelMusicOne = LevelMusicOneCue.Object;
  IntroMusicTwo = IntroMusicTwoCue.Object;
  OutroMusicTwo = OutroMusicTwoCue.Object;
  LevelMusicTwo = LevelMusicTwoCue.Object;
  VictoryMusic  = VictoryMusicCue.Object;
  GameOverMusic = DefeatMusicCue.Object;
}

void ABlockbreakerGameModeBase::Tick(float DeltaTime){
  Super::Tick(DeltaTime);
  if(RoundCountdownTime < 0.0 && State == EGameState::PLAYING){
    Time -= DeltaTime;
  }else if(State == EGameState::RESETTING){
    RoundCountdownTime -= DeltaTime;
  }
  CheckGameState(DeltaTime);
}

void ABlockbreakerGameModeBase::BeginPlay(){
  Super::BeginPlay();
  Init();
}

bool ABlockbreakerGameModeBase::Init(){
  PaddleLocation.X = 0.0f; PaddleLocation.Y = 1700.0f; PaddleLocation.Z = 96.0f;
  State = EGameState::STARTINGUP;
  return true;
}

int32 ABlockbreakerGameModeBase::Countdown(){
  return 0;
}

int32 ABlockbreakerGameModeBase::UpdateRoundTime(float DeltaTime){
  if(TimeRemainingCounter < 30){
    TimeRemainingTimer += DeltaTime;
    if(TimeRemainingTimer >= .1f){
      int32 Incrmt = (int32)((Time)/30.0);
      TimeRemainingTimer -= 0.1f;
      TimeRemainingCounter++;
      TimeRemaining -= (TimeRemainingCounter * Incrmt);
    }
    return TimeRemaining;
  } else {
    return 0;
  }
  return 0.0f;
}

int32 ABlockbreakerGameModeBase::UpdateCountdownTime(float DeltaTime){
  return 0;
}

int32 ABlockbreakerGameModeBase::UpdateScore(float DeltaTime, int32 PointTotal){
  if (ScoreUpdateCounter < 30){
    ScoreUpdateTimer += DeltaTime;
    if (ScoreUpdateTimer > 0.1f){
      int32 Incrmt = PointTotal/30;
      ScoreUpdateTimer -= 0.1f;
      ScoreUpdateCounter++;
      ScoreBonus += (ScoreUpdateCounter * Incrmt);
    }
  }
  return ScoreBonus;
}

int32 ABlockbreakerGameModeBase::UpdateFinalScore(float DeltaTime, int32 PointTotal){
  if(FinalScoreUpdateCounter < 30){
    FinalScoreUpdateTimer += DeltaTime;
    if(FinalScoreUpdateTimer > 0.1f){
      int32 Incrmt = PointTotal/30;
      FinalScoreUpdateTimer -= 0.1f;
      FinalScoreUpdateCounter++;
      FinalScore += (FinalScoreUpdateCounter * Incrmt);
    }
  }
  return FinalScore;
}

int32 ABlockbreakerGameModeBase::UpdateLives(float DeltaTime){
  if(LivesRemainingCounter < PlayerLives){
    LivesRemainingTimer += DeltaTime;
    if(LivesRemainingTimer >= 1.0f){
      LivesRemainingTimer -= 1.0f;
      Lives--;
    }
    return Lives;
  }else{
    return 0;
  }
}

int32 ABlockbreakerGameModeBase::UpdateAmmo(float DeltaTime){
  if(AmmoRemainingCounter < Ammo){
    AmmoRemainingTimer += DeltaTime;
    if(AmmoRemainingTimer >= 0.1f){
      int32 Incrmt = Ammo/ 30;
      AmmoRemainingTimer -= 1.0f;
      AmmoRemainingCounter++;
      AmmoRemaining -= (AmmoRemainingCounter * Incrmt);
      AmmoRemaining;
    }
    return AmmoRemaining;
  }else{
    return 0;
  }
}

void ABlockbreakerGameModeBase::NotifyBrickDeath(int32 Points){
  /////////////////////
  TriggerVictoryCondition();
///////////////////////
  BricksInLevel--;
  Score += Points;
  
  if(BricksInLevel <= 0){
    UE_LOG(LogTemp, Warning, TEXT("Match Won!\n\tFinalScore: %d"), Score);
    TriggerVictoryCondition();
  }
}

void ABlockbreakerGameModeBase::AddSphere(ALevelSphere* Sphere){
  check(Sphere != nullptr);
  ActiveSpheres.Add(Sphere);
  UE_LOG(LogTemp, Warning, TEXT("Sphere Added to GameMode"));
}

void ABlockbreakerGameModeBase::DeleteSphere(ALevelSphere* Sphere){
  check(Sphere != nullptr);
  ActiveSpheres.Remove(Sphere);
  SpheresPendingDeletion.Add(Sphere);
  Player->DeleteSphere(Sphere);
  if(ActiveSpheres.Num() <= 0){
    TriggerDefeatCondition();
  }
}

void ABlockbreakerGameModeBase::TriggerGameOver(){

}

void ABlockbreakerGameModeBase::TriggerGameExit(){

}

void ABlockbreakerGameModeBase::CheckGameState(float DeltaTime){
  switch (State) {
    case EGameState::STARTINGUP:
      ProcessStartUp();
      break;
    case EGameState::RESETTING:
      ProcessReset();
      break;
    case EGameState::PLAYING:
      ProcessPlaying();
      break;
    case EGameState::ROUNDWON:
      ProcessRoundWon();
      break;
    case EGameState::ROUNDSUMMARY:
      ProcessRoundSummary(DeltaTime);
      break;
    case EGameState::UPGRADING:
      ProcessUpgrading();
      break;
    case EGameState::ROUNDLOSS:
      ProcessRoundLoss();
      break;
    case EGameState::GAMELOSS:
      ProcessGameLoss();
      break;
    case EGameState::PAUSED:
      ProcessPaused();
      break;
    default:
    case EGameState::EXITING:
      ProcessExit();
      break;
  }
}

void ABlockbreakerGameModeBase::TriggerReset(){
  UE_LOG(LogTemp, Warning, TEXT("Triggering Reset"));
  ProcessReset();
}

void ABlockbreakerGameModeBase::TriggerResume(){

}

void ABlockbreakerGameModeBase::TriggerActivePlay(){
  UE_LOG(LogTemp, Warning, TEXT("Triggering Active Play"));
  Player->bCeasefire = false;
  if(!Player->bAlive){
    Player->bAlive = true;
  }
  this->MusicComponent->Play();
  State = EGameState::PLAYING;
}

void ABlockbreakerGameModeBase::TriggerPause(){
  bGamePaused = !bGamePaused;
}

void ABlockbreakerGameModeBase::TriggerVictoryCondition(){
  FVector SphereBrake(0.0f, 0.0f, 0.0f);
  for (ALevelSphere* S : ActiveSpheres){
    S->GetMovementComponent()->SetVelocityInLocalSpace(SphereBrake);
  }
  Player->bAlive = false;
  FinalScore = Score;
  State = EGameState::ROUNDSUMMARY;
}

void ABlockbreakerGameModeBase::TriggerDefeatCondition(){
  UE_LOG(LogTemp, Warning, TEXT("Triggering Defeat Condition"));
  ProcessRoundLoss();
}

void ABlockbreakerGameModeBase::ProcessStartUp(){
  if(FMath::RandBool()){
    this->SFXComponentOne->SetSound(IntroMusicOne);
    this->MusicComponent->SetSound(LevelMusicOne);
    this->SFXComponentTwo->SetSound(OutroMusicOne);
  }else{
    this->SFXComponentOne->SetSound(IntroMusicTwo);
    this->MusicComponent->SetSound(LevelMusicTwo);
    this->SFXComponentTwo->SetSound(OutroMusicTwo);
  }
  State = EGameState::STARTINGUP;
  ProcessReset();
}

void ABlockbreakerGameModeBase::ProcessReset(){
  if(State != EGameState::RESETTING){
    State = EGameState::RESETTING;
    if(SpheresPendingDeletion.Num() > 0){
      for(ALevelSphere* S : SpheresPendingDeletion){
        SpheresPendingDeletion.Remove(S);
        S->Destroy();
      }
    }
    
    if(Player == nullptr){
      FVector  PlayerLoc(0.0f, 1700.0f, 120.0f);
      FRotator PlayerRot(0.0f, 0.0f, 0.0f);

      FActorSpawnParameters PlayerSpawnInfo;
      PlayerSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
      Player = GetWorld()->SpawnActor<ALevelPaddle>(PlayerLoc, PlayerRot, PlayerSpawnInfo);
      Player->SetGameMode(this);
    }else{
      //  Move the Paddle back to it's starting position
      Player->SetActorLocation(PaddleLocation);
    }
    
    // Turn Paddle input on, but set Ceasefire to true to keep it from firing off the sphere before round activates
    Player->bCeasefire = true;
    Player->bAlive = true;

    FVector  SphereLoc(0.0f, 1700.0f, 124.0f);
    FRotator SphereRot(0.0f, 0.0f, 0.0f);

    FActorSpawnParameters SpawnInfo;
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    //  Toggle deflating to false, inPlay to false, gravity to 0.0, friction to 0.0
    ALevelSphere* ActiveSphere = GetWorld()->SpawnActor<ALevelSphere>(SphereLoc, SphereRot, SpawnInfo);
    
    Player->AddActiveSphere(ActiveSphere);
    ActiveSphere->SetPlayerPaddle(Player);
    
    //  Call play intro music
    this->SFXComponentOne->Play();

    //  Set A Timer to call TriggerActivePlay() after Five Seconds
    FTimerDelegate HandleDel = FTimerDelegate::CreateUObject(this, &ABlockbreakerGameModeBase::TriggerActivePlay);
    GetWorldTimerManager().SetTimer(StartUpTimer, HandleDel, 5.33f, false);
  }
}

void ABlockbreakerGameModeBase::ProcessPlaying(){

}

void ABlockbreakerGameModeBase::ProcessPaused(){

}

void ABlockbreakerGameModeBase::ProcessRoundWon(){
  if (State != EGameState::ROUNDWON){
    State = EGameState::ROUNDWON;
    MusicComponent->Stop();
    MusicComponent->SetSound(VictoryMusic);
    MusicComponent->Play();
  }
  State = EGameState::ROUNDSUMMARY;
}

void ABlockbreakerGameModeBase::ProcessRoundLoss(){
  if(State != EGameState::ROUNDLOSS){
    State = EGameState::ROUNDLOSS;
    PlayerLives--;
    this->MusicComponent->Stop();
    this->SFXComponentTwo->Play();
    FTimerHandle Handle;
    FTimerDelegate HandleDel;
    if(PlayerLives <= 0){
      UE_LOG(LogTemp, Warning, TEXT("Game Lost!\n\tFinal Score: %d"), Score);
      HandleDel = FTimerDelegate::CreateUObject(this, &ABlockbreakerGameModeBase::TriggerGameOver);
    }else{
      HandleDel = FTimerDelegate::CreateUObject(this, &ABlockbreakerGameModeBase::TriggerReset);
    }
    GetWorldTimerManager().SetTimer(Handle, HandleDel, 2.75f, false);
  }
}

void ABlockbreakerGameModeBase::ProcessUpgrading(){

}

void ABlockbreakerGameModeBase::ProcessGameLoss(){

}

void ABlockbreakerGameModeBase::ProcessExit(){

}
