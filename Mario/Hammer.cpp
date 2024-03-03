#include "Hammer.h"
#include "Mario.h"

Hammer::Hammer() 
{
}

Hammer::~Hammer() 
{
}

void Hammer::BeginPlay()
{
	SetName("Hammer");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetImage("Hammer.png");
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f);
	SetAnimation("Idle");
	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ {0,-10}, {100,20} });
	SpeedX.X = -150.f;
	SpeedY.Y = -250.f;
	Destroy(10.f);
}

void Hammer::Tick(float _DeltaTime)
{
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
		Player->Hit();
	}
}
