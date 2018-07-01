#include "LevelPaddle.h"
#include "LevelSphere.h"
#include "BlockbreakerGameModeBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


void FPaddleInput::Accelerate() {

}

void FPaddleInput::MoveX(float AxisValue){
  RawMovementInput.X += AxisValue;
  MovementInput = RawMovementInput.ClampAxes(-1.f, 1.f); // Set Limit on inputs
  MovementInput.GetSafeNormal(); // Normalizes diagonal inputs to conform to Unit Circle
  LastMovement = MovementInput;
  RawMovementInput.Set(0.f, 0.f);// Reset movement buffer each frame
}

void FPaddleInput::Fire1(bool bPressed){
  bFire1 = bPressed;
}

void FPaddleInput::Fire2(bool bPressed){
  bFire2 = bPressed;
}

void FPaddleInput::Pause(bool bPressed){
  bPause = bPressed;
}

// Sets default values
ALevelPaddle::ALevelPaddle(){
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  /* Set up Collision capsule */
  CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
  CollisionCapsule->SetWorldRotation(FRotator(0.0f, 0.0f, -90.0f));
  CollisionCapsule->SetCapsuleHalfHeight(48.0f);
  CollisionCapsule->SetCapsuleRadius(12.0f);
  CollisionCapsule->SetCollisionProfileName("Pawn");
  CollisionCapsule->OnComponentHit.AddDynamic(this, &ALevelPaddle::OnHit);
  CollisionCapsule->SetupAttachment(RootComponent);
  RootComponent = CollisionCapsule;
  /* Set up Paddle Mesh */
  StaticPaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  StaticPaddleMesh->SetupAttachment(CollisionCapsule);
  
  static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/Paddles/PaddleStaticMesh.PaddleStaticMesh'"));
  
  this->DefaultMesh = DefaultMeshAsset.Object;
  this->SetActiveMesh(EPaddleState::NORMAL);


  MoveSpeed = 250.f;
  this->PaddleState = EPaddleState::NORMAL;
  bAlive = true;

  DebugCounter = 0;

  AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
  AudioComponent->bAutoActivate = false;
  AudioComponent->SetupAttachment(RootComponent);

  static ConstructorHelpers::FObjectFinder<USoundCue> HitCue(TEXT("SoundCue'/Game/Assets/Audio/SoundEffects/HitPaddleCue.HitPaddleCue'"));
  HitSound = HitCue.Object;

  this->AutoPossessPlayer = EAutoReceiveInput::Player0;
  this->AutoReceiveInput = EAutoReceiveInput::Player0;

  bRequestingPause = false;
  bReceivingPauseBroadcast = false;
}

bool ALevelPaddle::SetActiveMesh(EPaddleState State){
  switch (State){
    case EPaddleState::NORMAL:
      this->StaticPaddleMesh->SetStaticMesh(DefaultMesh);
      return true;
    case EPaddleState::EXTENDED:
      UE_LOG(LogTemp, Warning, TEXT("Extended Mesh not implemented yet"));
      break;
    case EPaddleState::GUNS:
      UE_LOG(LogTemp, Warning, TEXT("Guns Mesh not implemented yet"));
      break;
    case EPaddleState::LASER:
      UE_LOG(LogTemp, Warning, TEXT("Laser Mesh not implemented yet"));
      break;
    default:
      break;
  }
  this->StaticPaddleMesh->SetStaticMesh(DefaultMesh);
  return true;
}

void ALevelPaddle::PlayHitSound(){ 
  if (AudioComponent){ 
    AudioComponent->Play(); 
  }
}

// Called to bind functionality to input
void ALevelPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  InputComponent->BindAxis("MoveX", this, &ALevelPaddle::MoveX);
  InputComponent->BindAction("Fire1", EInputEvent::IE_Pressed, this, &ALevelPaddle::Fire1Pressed);
  InputComponent->BindAction("Fire1", EInputEvent::IE_Released, this, &ALevelPaddle::Fire1Released);
  InputComponent->BindAction("Fire2", EInputEvent::IE_Pressed, this, &ALevelPaddle::Fire2Pressed);
  InputComponent->BindAction("Fire2", EInputEvent::IE_Released, this, &ALevelPaddle::Fire2Released);
  InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &ALevelPaddle::PausePressed);
}

// Called when the game starts or when spawned
void ALevelPaddle::BeginPlay(){
  Super::BeginPlay();
  if (HitSound->IsValidLowLevelFast()){
    AudioComponent->SetSound(HitSound);
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Paddle Hit Sound isn't valid."));
  }
}

// Called every frame
void ALevelPaddle::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  if (!bAlive || bReceivingPauseBroadcast){
    if (DebugCounter >= 2.0) {
      DebugCounter -= 2.0;
    }
    UE_LOG(LogTemp, Warning, TEXT("Paddle Is not Alive!"));
    return;
  }else{
    DebugCounter += DeltaTime;

    /* Get Desired movement */
    FVector DesiredMovementDirection;
    DesiredMovementDirection.X = PaddleInput.MovementInput.X;

    /* If Movement has a significant value */
    if (!DesiredMovementDirection.IsNearlyZero()) {

      /* Get current location */
      FVector Pos = GetActorLocation();
      float DeltaMovement = DesiredMovementDirection.X * MoveSpeed * DeltaTime;

      /* Update current location with movement info */
      Pos.X += DeltaMovement;

      /* Set new location after sweeping for collision */
      SetActorLocation(Pos, true);
    }
  }
}

void ALevelPaddle::MoveX(float AxisValue){
  if(DebugCounter >= 2.5f && AxisValue != 0.0f){
    DebugCounter = 0.0f;
  }
  PaddleInput.MoveX(AxisValue);
}

void ALevelPaddle::Fire1Pressed(){
  if (!bCeasefire) {
    UE_LOG(LogTemp, Warning, TEXT("InFire1Pressed()"));
    for (ALevelSphere* ActiveSphere : ActiveSpheres){
      UE_LOG(LogTemp, Warning, TEXT("ActiveSphere: %s"), *ActiveSphere->GetActorLabel());
      if (!ActiveSphere->IsInPlay()) {
        ActiveSphere->ToggleActive();
      }
    }
    switch (this->PaddleState) {
      case EPaddleState::GUNS:

        break;
      case EPaddleState::LASER:

        break;
      case EPaddleState::CATCHER:

        break;
    }
  }
}

void ALevelPaddle::Fire1Released(){
  if(PaddleState == EPaddleState::CATCHER){

  }
}

void ALevelPaddle::Fire2Pressed() {
  
}

void ALevelPaddle::Fire2Released() {

}

void ALevelPaddle::PausePressed(){

}

void ALevelPaddle::OnHit_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  if (ALevelSphere* Sphere = Cast<ALevelSphere>(OtherActor)){
    AudioComponent->Play();
  }
}

void ALevelPaddle::OnOverlapBegin_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Paddle has detected Begin Overlap from %s"), *OtherActor->GetName());
}

void ALevelPaddle::OnOverlapEnd_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Paddle has detected End Overlap from %s"), *OtherActor->GetName());
}