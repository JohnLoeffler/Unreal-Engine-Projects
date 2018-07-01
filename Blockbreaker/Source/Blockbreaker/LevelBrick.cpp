
#include "LevelBrick.h"
#include "LevelSphere.h"
#include "Components/StaticMeshComponent.h"
#include "BlockbreakerGameModeBase.h"
#include "Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


ALevelBrick::ALevelBrick() {
  BaseHealth = 1.0;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
  Mesh->OnComponentHit.AddDynamic(this, &ALevelBrick::OnHit);
  Mesh->SetupAttachment(RootComponent);
  RootComponent = Mesh;

  static ConstructorHelpers::FObjectFinder<UStaticMesh> StandardMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Standard.Standard'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> HardenedMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Hardened.Hardened'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> ReinforcedMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Reinforced.Reinforced'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> BombMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/BaseBombBrick.BaseBombBrick'"));
  
  StandardMeshAsset = StandardMesh.Object;
  HardenedMeshAsset = HardenedMesh.Object;
  ReinforcedMeshAsset = ReinforcedMesh.Object;
  BombMeshAsset = BombMesh.Object;

  AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
  AudioComponent->bAutoActivate = false;
  AudioComponent->SetupAttachment(RootComponent);

  static ConstructorHelpers::FObjectFinder<USoundCue> HitCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/HitSoundCue.HitSoundCue'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> BreakSoundCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/BreakSoundCue.BreakSoundCue'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> DestroyCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/DestroyedSoundCue.DestroyedSoundCue'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> ReinforcedBreakSoundCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/ReinforcedBreak.ReinforcedBreak'"));
  static ConstructorHelpers::FObjectFinder<USoundCue> BombBreakSoundCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/BombSoundCue.BombSoundCue'"));
  
  HitSound = HitCue.Object;
  this->BreakSound = BreakSoundCue.Object;
  this->ReinforcedBreakSound = ReinforcedBreakSoundCue.Object;
  DestroyedSound = DestroyCue.Object;

  BaseHealth = 1.0f;
  bRecentlyDamaged = false;
  bImpervious = false;
  Resistance = 0.25f;
}

ALevelBrick::~ALevelBrick(){}

void ALevelBrick::Tick(float DeltaTime){
  Super::Tick(DeltaTime);
  bRecentlyDamaged = false;
}

void ALevelBrick::BeginPlay(){
  Super::BeginPlay();
  Init();
}

void ALevelBrick::DamageBrick(float Damage){
  BaseHealth -= Damage;
}

void ALevelBrick::SetBrickColor(FVector Color){
  if (MaterialInstances.Num() > 0){
    MaterialInstances[0]->SetVectorParameterValue("Color", Color);
  }
}

bool ALevelBrick::Init(){return true;}

void ALevelBrick::SetBrickType(EBrickType Type){
  switch(Type){
    case EBrickType::HARDENED:
      BaseHealth = 2.0;
      Resistance = 0.34f;
      Points = 250;
      if(Mesh){
        Mesh->SetStaticMesh(HardenedMeshAsset);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Mesh->SetCollisionProfileName("Brick");
      }
      break;
    case EBrickType::REINFORCED:
      BaseHealth = 3.0;
      Resistance = 0.5f;
      Points = 375;
      if(Mesh){
        Mesh->SetStaticMesh(ReinforcedMeshAsset);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Mesh->SetCollisionProfileName("Brick");
      }
      break;
    case EBrickType::BOMB:
      BaseHealth = 1.0;
      Resistance = 0.0f;
      Points = 175;
      if(Mesh){
        Mesh->SetStaticMesh(BombMeshAsset);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Mesh->SetCollisionProfileName("Brick");
      }
      break;
    case EBrickType::STANDARD:
      BaseHealth = 1.0;
      Resistance = 0.25f;
      Points = 125;
      if(Mesh){
        Mesh->SetStaticMesh(StandardMeshAsset);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Mesh->SetCollisionProfileName("Brick");
      }
      break;
    case EBrickType::EMPTY:
    default:
      if(Mesh){
        BaseHealth = 0.0;
        Resistance = 1.0f;
        Mesh->SetStaticMesh(nullptr);
        Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Mesh->SetCollisionProfileName("IgnoreAll");
      }
      break;
  }
  TArray<UMaterialInterface*> MatInterfaces = this->Mesh->GetMaterials();
  int index = 0;
  for(UMaterialInterface* UMI : MatInterfaces){
    MaterialInstances.Add(this->Mesh->CreateDynamicMaterialInstance(index, UMI));
    if(!MaterialInstances[index]){
      UE_LOG(LogTemp, Warning, TEXT("Error Assigning Material Instance"));
    }
    index++;
  }
}

EBrickType ALevelBrick::GetBrickType(){
  return EBrickType();
}

void ALevelBrick::SetBrickNumber(int32 Num){
  BrickNumber = Num;
}

void ALevelBrick::SetGameModeRef(AGameModeBase* Ref){
  GameMode = Cast<ABlockbreakerGameModeBase>(Ref);
}

void ALevelBrick::HitWithWaveform(float Force, float TimerDelay){
  if(bImpervious){
    return;
  }
  
  if(bRecentlyDamaged){
    return;
  }

  float NewForce = Force - (Force*Resistance);
  
  if(NewForce <= 0.0){
    return;
  }
  
  bRecentlyDamaged = true;

  if (AboveBrick != nullptr){
    this->AboveBrick->HitWithWaveform(NewForce, TimerDelay + 0.25);
    UE_LOG(LogTemp, Warning, TEXT("Hitting Brick number %d with force %f"), AboveBrick->BrickNumber, NewForce);
  }
  if (LeftBrick != nullptr){
    this->LeftBrick->HitWithWaveform(NewForce, TimerDelay + 0.25);
    UE_LOG(LogTemp, Warning, TEXT("Hitting Brick number %d with force %f"), LeftBrick->BrickNumber, NewForce);
  }
  if (BelowBrick != nullptr){
    this->BelowBrick->HitWithWaveform(NewForce, TimerDelay + 0.25);
    UE_LOG(LogTemp, Warning, TEXT("Hitting Brick number %d with force %f"), BelowBrick->BrickNumber, NewForce);
  }
  if (RightBrick != nullptr){
    this->RightBrick->HitWithWaveform(NewForce, TimerDelay + 0.25);
    UE_LOG(LogTemp, Warning, TEXT("Hitting Brick number %d with force %f"), RightBrick->BrickNumber, NewForce);
  }
  FTimerHandle Handle;
  FTimerDelegate HandleDel = FTimerDelegate::CreateUObject(this, &ALevelBrick::DamageBrick, NewForce);
  GetWorldTimerManager().SetTimer(Handle, HandleDel, TimerDelay, false);
}

void ALevelBrick::OnHit_Implementation(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult & Hit){
  float OldHealth = BaseHealth;
  UE_LOG(LogTemp, Warning, TEXT("LevelBrick reports collision with %s"), *OtherActor->GetName());
  if (ALevelSphere* Sphere = Cast<ALevelSphere>(OtherActor)){
    DamageBrick(Sphere->GetSphereDamage());
    UE_LOG(LogTemp, Warning, TEXT("Old Health: %f | New Health: %f "),OldHealth, BaseHealth);
    if (BaseHealth <= 0.0){
      AudioComponent->SetSound(DestroyedSound);
      if (DestroyedSound->IsValidLowLevelFast()) {
        AudioComponent->bStopWhenOwnerDestroyed = false;
        AudioComponent->Play();
      }
      GameMode->NotifyBrickDeath(Points);
      this->Destroy();
    } else if( (OldHealth > 2.0 && (BaseHealth <=2.0 && BaseHealth > 1.0) )){
      this->SetBrickType(EBrickType::HARDENED);
      AudioComponent->SetSound(ReinforcedBreakSound);
      if (DestroyedSound->IsValidLowLevelFast()){
        AudioComponent->bStopWhenOwnerDestroyed = false;
        UE_LOG(LogTemp, Warning, TEXT("Playing Reinforced Break Sound"));
        AudioComponent->Play();
      }
    }else if(OldHealth > 1.0 && (BaseHealth <=1.0 && BaseHealth > 0.0)){
      this->SetBrickType(EBrickType::STANDARD);
      AudioComponent->SetSound(BreakSound);
      if (BreakSound->IsValidLowLevelFast()) {
        AudioComponent->bStopWhenOwnerDestroyed = false;
        UE_LOG(LogTemp, Warning, TEXT("Playing Hardened Break Sound"));
        AudioComponent->Play();
      }
    }else{
      AudioComponent->SetSound(HitSound);
      if(HitSound->IsValidLowLevelFast()){
        AudioComponent->bStopWhenOwnerDestroyed = false;
        UE_LOG(LogTemp, Warning, TEXT("Playing Hardened Break Sound"));
        AudioComponent->Play();
      }
    }
  }
}
