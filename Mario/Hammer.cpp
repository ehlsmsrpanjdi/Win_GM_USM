#include "Hammer.h"
#include "Mario.h"
#include "MarioHelper.h"

Hammer::Hammer() 
{
}

Hammer::~Hammer() 
{
}

void Hammer::BeginPlay()
{
	SetName("Hammer");
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetTransform({ { 0,0 }, { 64,64 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f);
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ {0,-10}, {100,20} });
	SpeedY.Y = -250.f;

	Destroy(10.f);
}

void Hammer::Tick(float _DeltaTime)
{
	if (MarioHelper::GameEnd) {
		Destroy();
	}
	GravitySpeed.Y += _DeltaTime * 200.f;
	ResultMove(_DeltaTime);
	CollisionEvent(_DeltaTime);
}

void Hammer::CollisionEvent(float _DeltaTime)
{
	FVector ThisPosition = this->GetActorLocation();
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		UCollision* Collision = Result[0];
		Mario* Player = (Mario*)Collision->GetOwner();
		if (Player->GetState() == MarioState::EndingMove) {
			return;
		}
		Player->Hit();
	}
}

void Hammer::SetDir(EActorDir _KoopaDir)
{
	if (EActorDir::Left == _KoopaDir) {
		DirState = EActorDir::Left;
		SpeedX.X = -200.f;
	}
	else {
		DirState = EActorDir::Right;
		SpeedX.X = 200.f;
	}
	SetAnimation("Idle");
}
