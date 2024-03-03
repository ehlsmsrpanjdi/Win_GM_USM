#include "Koopa.h"
#include "KoopaFire.h"
#include "Hammer.h"
#include "Mario.h"

Koopa::Koopa()
{
}

Koopa::~Koopa()
{
}

void Koopa::BeginPlay()
{
	MonsterBase::BeginPlay();
	NoDir = true;
	SetName("Koopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Koopa.png");
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.2f);
	SetAnimation("Idle");
	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ {0,-10}, {100,20} });
	SpeedX.X = -50.f;

}

void Koopa::Tick(float _DeltaTime)
{
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);

	Attack(_DeltaTime);
	Jump(_DeltaTime);
}

void Koopa::Attack(float _DeltaTime)
{
	if (FireTime > 0) {
		FireTime -= _DeltaTime;
	}
	else {
		KoopaFire* Fire = GetWorld()->SpawnActor<KoopaFire>(MarioRenderOrder::Monster);
		float X = GetActorLocation().X;
		float Y = GetActorLocation().Y;
		Fire->SetActorLocation({ X,Y - 50 });
		FireTime = 2.0f;
	}

	if (HammerTime > 2.f) {
		HammerTime -= _DeltaTime;
	}
	else  if (HammerTime > 0.f) {
		HammerTime -= _DeltaTime;
		if (HammerCoolTime > 0.f) {
			HammerCoolTime -= _DeltaTime;
		}
		else {
			Hammer* Hama = GetWorld()->SpawnActor<Hammer>(MarioRenderOrder::Monster);
			float X = GetActorLocation().X;
			float Y = GetActorLocation().Y;
			Hama->SetActorLocation({ X,Y - 50 });
			HammerCoolTime = 0.2f;
		}
	}
	else {
		HammerTime = 4.0f;
	}
}

void Koopa::Jump(float _DeltaTime)
{
	if (JumpTime > 0) {
		JumpTime -= _DeltaTime;
	}
	else {
		JumpTime = 3.0f;
		SpeedY.Y = -600.f;
		AddActorLocation(FVector::Up * 5);
	}
}


void Koopa::CollisionEvent(float _DeltaTime)
{
	FVector ThisPosition = this->GetActorLocation();
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		UCollision* Collision = Result[0];
		Mario* Player = (Mario*)Collision->GetOwner();
		Player->Hit();
	}
}
