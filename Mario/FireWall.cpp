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
		FireWallRenderer[i] = CreateImageRenderer(MarioRenderOrder::Monster);
		FireWallRenderer[i]->SetImage("Fire.png");
		FVector Pos = RightVector * 16.0f * i;
		FireWallRenderer[i]->SetTransform({ Pos, {128 , 128} });
		AnimationAuto(FireWallRenderer[i], "Idle", 0, 3);
		FireWallRenderer[i]->ChangeAnimation("Idle");
	}

	for (int i = 0; i < 6; ++i) {
		FireWallCollision[i] = CreateCollision(MarioCollisionOrder::Monster);
		FireWallCollision[i]->SetTransform({ {0 + i * 16,0}, {16 , 16} });
	}
	//BodyCollision = CreateCollision(MarioCollisionOrder::Fire);
	//BodyCollision->SetColType(ECollisionType::Rect);
	//BodyCollision->SetTransform({ { 0,-16 }, { 32, 32 } });
}

void FireWall::Tick(float _DeltaTime)
{
	PhysicsActor::Tick(_DeltaTime);
	Spin(_DeltaTime);

	CollisionEvent(_DeltaTime);
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
		FVector Pos = RightVector * 18.0f * i;
		Pos.RotationZToDeg(Angle);
		FireWallRenderer[i]->SetTransform({ Pos, {128 , 128} });
	}

	for (int i = 0; i < 6; ++i)
	{
		FVector Pos = RightVector * 18.0f * i;
		Pos.RotationZToDeg(Angle);
		FireWallCollision[i]->SetTransform({ Pos, {16 ,16} });
	}
	
}

