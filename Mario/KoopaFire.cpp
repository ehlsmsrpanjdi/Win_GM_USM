#include "KoopaFire.h"
#include "Mario.h"

KoopaFire::KoopaFire() 
{
}

KoopaFire::~KoopaFire() 
{
}

void KoopaFire::BeginPlay()
{
	SetName("Koopa");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetImage("Koopa.png");
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 6, 7, 0.2f);
	SetAnimation("Idle");
	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ {0,-10}, {100,20} });
	SpeedX.X = -300.f;
	Destroy(10.f);
}

void KoopaFire::Tick(float _DeltaTime)
{
	ResultMove(_DeltaTime);
	CollisionEvent(_DeltaTime);
}

void KoopaFire::CollisionEvent(float _DeltaTime)
{
	FVector ThisPosition = this->GetActorLocation();
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		UCollision* Collision = Result[0];
		Mario* Player = (Mario*)Collision->GetOwner();
		Player->Hit();
	}
}
