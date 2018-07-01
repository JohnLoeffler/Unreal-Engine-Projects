#include "LevelSphere.h"
#include "LevelBrick.h"
#include "LevelPaddle.h"
#include "LevelArch.h"
#include "LevelFloor.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BlockbreakerGameModeBase.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ALevelSphere::ALevelSphere()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  USphereComponent *SphereCollision;

  SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  SphereCollision->InitSphereRadius(6.0f);
  SphereCollision->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
  SphereCollision->OnComponentHit.AddDynamic(this, &ALevelSphere::OnHit);

  RootComponent = SphereCollision;
  
  MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  MeshComponent->SetMobility(EComponentMobility::Movable);
  MeshComponent->SetupAttachment(SphereCollision);

  //BallDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("BallDirection"));
  //BallDirection->SetupAttachment(SphereCollision);

  // Use a ProjectileMovementComponent to govern this projectile's movement
  SphereMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  
  SphereMovement->UpdatedComponent = SphereCollision;
  SphereMovement->InitialSpeed = 320.0f;
  SphereMovement->MaxSpeed = 320.0f;
  SphereMovement->bRotationFollowsVelocity = false;
  SphereMovement->SetPlaneConstraintEnabled(true);
  SphereMovement->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
  SphereMovement->bShouldBounce = true;
  SphereMovement->Bounciness = 1.0;
  SphereMovement->Friction = 0.0;
  SphereMovement->ProjectileGravityScale = 0.0f;
  this->bInPlay = false;
  this->bDeflating = false;
  this->Damage = 1.0f;
  
  static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT(
    "StaticMesh'/Game/Assets/Meshes/Spheres/DefaultSphere.DefaultSphere'"));
  DefaultMesh = DefaultMeshAsset.Object;
  
//  DefaultTimer = 0.0;
}

void ALevelSphere::Reset(){
  this->Damage = 1.0f;
  this->MeshComponent->SetStaticMesh(DefaultMesh);
  UE_LOG(LogTemp, Warning, TEXT("Finished Resetting Sphere"));
}

bool ALevelSphere::Init(){
  Reset();
  if(DefaultMesh){
    TArray<UMaterialInterface*> MatInterfaces = this->MeshComponent->GetMaterials();
    int index = 0;
    for (UMaterialInterface* UMI : MatInterfaces) {
      MaterialInstances.Add(this->MeshComponent->CreateDynamicMaterialInstance(index, UMI));
      if (!MaterialInstances[index]) {
        UE_LOG(LogTemp, Warning, TEXT("Error retrieving the material instance [%d] for %s"), index, *(GetNameSafe(this)));
        return false;
      }
      index++;
    }
    UE_LOG(LogTemp, Warning, TEXT("Successfully set Mesh for the Sphere"));
  }else{
    UE_LOG(LogTemp, Warning, TEXT("Unable to set Mesh for the Sphere in Init"));
  }
    
  if(GetWorld()){
    GameMode = Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode());
    if(GameMode){
      GameMode->AddSphere(this);
    }else{
      UE_LOG(LogTemp, Warning, TEXT("Error retreiving the GameMode in ALevelSphere::Init()"));
    }
  }
  return true;
}

void ALevelSphere::ToggleActive(){
  this->bInPlay = !this->bInPlay;
  if (bInPlay) {
    SphereMovement->InitialSpeed = 320.0f;
    SphereMovement->MaxSpeed = 320.0f;
    FVector SphereVelocity(320.0f, 0.0f, 320.0f);
    if (FMath::RandBool()){
      SphereVelocity.X *= 1.0;
    } else {
      SphereVelocity.X *= -1.0;
    }
      SphereVelocity.Z = SphereMovement->InitialSpeed;
      GetMovementComponent()->SetVelocityInLocalSpace(SphereVelocity);
  }
}

void ALevelSphere::SetSpherePosition(float DeltaMovement) {
  //  If the ball is in play, this function should not change the balls position, so return
  if (this->IsInPlay()) {
    return;
  }
  FVector Pos = GetActorLocation();
  Pos.X += DeltaMovement;
  SetActorLocation(Pos);
}

// Called when the game starts or when spawned
void ALevelSphere::BeginPlay(){
  Super::BeginPlay();
  if (!Init()) {
    UE_LOG(LogTemp, Warning, TEXT("Error Occured while Initializing the Sphere"));
  }
}

// Called every frame
void ALevelSphere::Tick(float DeltaTime){
  Super::Tick(DeltaTime);
  DefaultTimer += DeltaTime;
  if (!bDeflating){
    if (!IsInPlay()){
      float DeltaMovement = PlayerPaddle->GetPaddlePosition().X - GetActorLocation().X;
      SetSpherePosition(DeltaMovement);
    } else if (fabs(GetMovementComponent()->Velocity.Z) < 75.0f && IsInPlay()) {
      float Direction = GetMovementComponent()->Velocity.Z;
      (Direction < 0 ? GetMovementComponent()->Velocity.Z -= 50.0 : GetMovementComponent()->Velocity.Z += 50.0);
    }
  } else if (LastPosition == this->GetActorLocation() && this->bInPlay && !this->bDeflating){
    GetMovementComponent()->Velocity.Z += 1.0;
  }else {
    
    if (GetMovementComponent()->Velocity.Z > 0.0){
      GetMovementComponent()->Velocity.Z -= DeltaTime * 250.0f;
    }

    if (GetMovementComponent()->Velocity.X > 0.0) {
      GetMovementComponent()->Velocity.X -= DeltaTime * 250.0f;
    }
  }
  if (DefaultTimer >= 2.0) {
    UE_LOG(LogTemp, Warning, TEXT("Sphere velocity: |X| %f |Y| %f |Z| %f"), GetMovementComponent()->Velocity.X, GetMovementComponent()->Velocity.Y, GetMovementComponent()->Velocity.Z);
    DefaultTimer -= 2.0;
  }
  LastPosition = this->GetActorLocation();
}

void ALevelSphere::InitSphereDeaden(){
  bDeflating = true;
  SphereMovement->Bounciness = 0.6;
  SphereMovement->ProjectileGravityScale = 1.0f;
  SphereMovement->Friction = 0.4f;
}

void ALevelSphere::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit){
  UE_LOG(LogTemp, Warning, TEXT("Ball reports a collision with %s"), *OtherActor->GetName());
  if (ALevelFloor* Floor = Cast<ALevelFloor>(OtherActor)){
    UE_LOG(LogTemp, Warning, TEXT("%s hit %s, notifying GameMode..."), *GetName(), *(Floor->GetName()));
    Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode())->DeleteSphere(this);
    InitSphereDeaden();
  }
}
