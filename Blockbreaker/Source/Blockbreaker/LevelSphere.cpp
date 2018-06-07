#include "LevelSphere.h"
#include "LevelBrick.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

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
  SphereCollision->SetupAttachment(RootComponent);

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  Mesh->SetupAttachment(SphereCollision);

  //BallDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("BallDirection"));
  //BallDirection->SetupAttachment(SphereCollision);

  // Use a ProjectileMovementComponent to govern this projectile's movement
  SphereMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  SphereMovement->UpdatedComponent = SphereCollision;
  SphereMovement->InitialSpeed = 320.0f;
  SphereMovement->MaxSpeed = 320.0f;
  SphereMovement->bRotationFollowsVelocity = false;
  SphereMovement->bShouldBounce = true;
  this->bInPlay = false;
  this->Damage = 1.0f;
}

void ALevelSphere::SetSpherePosition(float DeltaMovement) {
  //  If the ball is in play, this function should not change the balls position, so return
  if (this->IsInPlay()) {
    return;
  }
  FVector Pos = GetActorLocation();
  Pos.X += DeltaMovement;
}

// Called when the game starts or when spawned
void ALevelSphere::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ALevelSphere::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  if (IsInPlay()) {

  }
}

void ALevelSphere::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
  UE_LOG(LogTemp, Warning, TEXT("Ball reports a collision with %s"), *OtherActor->GetName());
  if (ALevelBrick* BrickHit = Cast<ALevelBrick>(OtherActor)) {
    BrickHit->DamageBrick(this->Damage);
  }
}