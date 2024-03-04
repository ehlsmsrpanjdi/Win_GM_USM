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
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 6, 7, 0.2f);
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ {0,-10}, {100,20} });
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

void KoopaFire::SetDir(EActorDir _KoopaDir)
{
	if (EActorDir::Left == _KoopaDir) {
		DirState = EActorDir::Left;
		SpeedX.X = -300.f;
	}
	else {
		DirState = EActorDir::Right;
		SpeedX.X = 300.f;
	}
	SetAnimation("Idle");
}
