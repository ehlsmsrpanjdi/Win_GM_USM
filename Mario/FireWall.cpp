#include "FireWall.h"
#include "Mario.h"

FireWall::FireWall()
{
}

FireWall::~FireWall()
{
}

void FireWall::BeginPlay()
{
	NoDir = true;
	AActor::BeginPlay();
	SetName("Fire");

	FVector RightVector = FVector::Right;

	for (int i = 0; i < 6; ++i) {
		FireWallRenderer[i] = CreateImageRenderer(MarioRenderOrder::Fire);
		FireWallRenderer[i]->SetImage("Fire.png");
		FVector Pos = RightVector * (float)(32 * i);
		FireWallRenderer[i]->SetTransform({ Pos, {256 , 256} });
		AnimationAuto(FireWallRenderer[i], "Idle", 0, 3);
		FireWallRenderer[i]->ChangeAnimation("Idle");
	}

	for (int i = 0; i < 6; ++i) {
		FireWallCollision[i] = CreateCollision(MarioCollisionOrder::Object);
		FireWallCollision[i]->SetTransform({ {0 + i * 16, 16}, {32 , 32} });
	}
}

void FireWall::Tick(float _DeltaTime)
{
	PhysicsActor::Tick(_DeltaTime);
	Spin(_DeltaTime);
}

void FireWall::CollisionEvent(float _DeltaTime)
{
	for (int i = 0; i < 6; ++i) {
		std::vector<UCollision*> Result;
		if (true == FireWallCollision[i]->CollisionCheck(MarioCollisionOrder::Player, Result)) {
			Mario* Player = static_cast<Mario*>(Result[0]->GetOwner());
			Player->Hit();
		}
	}
}

void FireWall::SetRight(bool _IsRight)
{
	if (_IsRight) {
		IsRight = 1.0f;
		return;
	}
	IsRight = -1.0;
	return;
}

void FireWall::Spin(float _DeltaTime)
{
	FVector RightVector = FVector::Right;

	Angle += 180.0f * _DeltaTime * IsRight;

	for (int i = 0; i < 6; ++i)
	{
		FVector Pos = RightVector * float(24 * i);
		Pos.RotationZToDeg(Angle);
		FVector a = Pos;
		FireWallRenderer[i]->SetTransform({ Pos, {192 , 192} });
	}

	for (int i = 0; i < 6; ++i)
	{
		FVector Pos = RightVector * float(24* i);
		Pos.RotationZToDeg(Angle);
		FireWallCollision[i]->SetTransform({ {Pos.X, Pos.Y - 12}, {24 ,24} });
	}
	
}

