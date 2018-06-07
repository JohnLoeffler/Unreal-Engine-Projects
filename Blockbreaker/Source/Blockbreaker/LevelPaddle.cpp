#include "LevelPaddle.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LevelSphere.h"

void FPaddleInput::Accelerate() {

}

void FPaddleInput::MoveX(float AxisValue) {
  RawMovementInput.X += AxisValue;
  MovementInput = RawMovementInput.ClampAxes(-1.f, 1.f); // Set Limit on inputs
  MovementInput.GetSafeNormal(); // Normalizes diagonal inputs to conform to Unit Circle
  LastMovement = MovementInput;
  RawMovementInput.Set(0.f, 0.f);// Reset movement buffer each frame
}

void FPaddleInput::Fire1(bool bPressed) {
  bFire1 = bPressed;
}

void FPaddleInput::Fire2(bool bPressed) {
  bFire2 = bPressed;
}

// Sets default values
ALevelPaddle::ALevelPaddle()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
  RootComponent = CollisionCapsule;
  CollisionCapsule->SetCollisionProfileName("Pawn");
  CollisionCapsule->OnComponentHit.AddDynamic(this, &ALevelPaddle::OnHit);

  PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  PaddleMesh->SetupAttachment(CollisionCapsule);

  MoveSpeed = 160.f;
  this->PaddleState = PaddleState::NORMAL;
  bAlive = true;

  DebugCounter = 0;
}

// Called to bind functionality to input
void ALevelPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  InputComponent->BindAxis("MoveX", this, &ALevelPaddle::MoveX);
  InputComponent->BindAction("Fire1", EInputEvent::IE_Pressed, this, &ALevelPaddle::Fire1Pressed);
  InputComponent->BindAction("Fire1", EInputEvent::IE_Released, this, &ALevelPaddle::Fire1Released);
  InputComponent->BindAction("Fire2", EInputEvent::IE_Pressed, this, &ALevelPaddle::Fire2Pressed);
  InputComponent->BindAction("Fire2", EInputEvent::IE_Released, this, &ALevelPaddle::Fire2Released);
}

// Called when the game starts or when spawned
void ALevelPaddle::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ALevelPaddle::Tick(float DeltaTime) {

  Super::Tick(DeltaTime);
  DebugCounter += DeltaTime;
  bHitWall = false;
  FVector DesiredMovementDirection;
  DesiredMovementDirection.X = PaddleInput.MovementInput.X;
  if (!DesiredMovementDirection.IsNearlyZero()) {
    FVector Pos = GetActorLocation();
    //FVector BPos = ActiveSphere->GetSphereLocation();
    float DeltaMovement = DesiredMovementDirection.X * MoveSpeed * DeltaTime;

    Pos.X += DeltaMovement;
    SetActorLocation(Pos, true);
    /*if (!bHitWall && !ActiveSphere->IsInPlay()) {
      BPos.X += DeltaMovement;
      ActiveSphere->SetActorLocation(BPos, true);
    }*/
  }
}

void ALevelPaddle::MoveX(float AxisValue) {
  if (DebugCounter >= 2.5f && AxisValue != 0.0f) {
    DebugCounter = 0.0f;
    UE_LOG(LogTemp, Warning, TEXT("In Paddle::MoveX, AxisValue == %f"), AxisValue);
  }
  PaddleInput.MoveX(AxisValue);
}

void ALevelPaddle::Fire1Pressed() {

}

void ALevelPaddle::Fire1Released() {
  UE_LOG(LogTemp, Warning, TEXT("In Fire1..."));
  if (DebugCounter > 2.0) {
    UE_LOG(LogTemp, Warning, TEXT("In FireReleased, 2 seconds passed..."));
    if (!ActiveSphere->IsInPlay()) {
      UE_LOG(LogTemp, Warning, TEXT("ActiveSphere not in play yet."));
      ActiveSphere->ToggleActive();
      if (ActiveSphere->IsInPlay()) {
        ActiveSphere->GetMovementComponent()->Velocity.Z = ActiveSphere->GetMovementComponent()->MaxSpeed;
        UE_LOG(LogTemp, Warning, TEXT("ActiveSphere now in play."));
        UE_LOG(LogTemp, Warning, TEXT("ActiveSphere velocity is: X| %d Y| %d Z| %d."), ActiveSphere->GetMovementComponent()->Velocity.X, ActiveSphere->GetMovementComponent()->Velocity.Y, ActiveSphere->GetMovementComponent()->Velocity.Z);
      }
    }
  }
}

void ALevelPaddle::Fire2Pressed() {

}

void ALevelPaddle::Fire2Released() {

}

void ALevelPaddle::OnHit_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Paddle has detected collision from %s"), *OtherActor->GetName());
  
}

void ALevelPaddle::OnOverlapBegin_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Paddle has detected Begin Overlap from %s"), *OtherActor->GetName());
}

void ALevelPaddle::OnOverlapEnd_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Paddle has detected End Overlap from %s"), *OtherActor->GetName());
}