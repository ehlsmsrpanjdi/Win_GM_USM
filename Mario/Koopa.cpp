#include "Koopa.h"
#include "KoopaFire.h"
#include "Hammer.h"
#include "Mario.h"

Koopa::Koopa()
{
}

Koopa::~Koopa()
{
	int a = 0;
}

void Koopa::BeginPlay()
{
	MonsterBase::BeginPlay();
	SetName("Koopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.2f);

	SetAnimation("Idle");
}

void Koopa::Tick(float _DeltaTime)
{
	PhysicsActor::Tick(_DeltaTime);


	if (KoopaDead(_DeltaTime)) {
		return;
	}


	float CameraX = GetWorld()->GetCameraPos().X;
	float WindowCenter = GEngine->MainWindow.GetWindowScale().X;
	float CurLocationX = GetActorLocation().X;
	if (CameraX + WindowCenter * 2 < CurLocationX)
	{
		return;
	}
	else if (!IsInit) {
		IsInit = true;
		MonsterInit();
	}

	SetAnimation("Idle");
	if (ChangeTime >= 0) {
		ChangeTime -= _DeltaTime;
		if (Mario::PlayerLocation.X > GetActorLocation().X) {
			DirState = EActorDir::Right;
			SpeedX.X = 50.f;
		}
		else {
			DirState = EActorDir::Left;
			SpeedX.X = -50.f;
		}
	}
	else {
		ChangeTime = 2.0f;
	}

	GravityCheck(_DeltaTime);
	CollisionEvent(_DeltaTime);
	ResultMove(_DeltaTime);

	if (KoopaExcute == true) {
		return;
	}

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
		Fire->SetDir(DirState);
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
			Hama->SetDir(DirState);
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
		SpeedY.Y = -400.f;
		AddActorLocation(FVector::Up * 5);
	}
}

bool Koopa::KoopaDead(float _DeltaTime)
{
	if (MarioHelper::GameEnd) {
		SpeedX.X = 0;
		GravitySpeed += MarioHelper::Gravity * _DeltaTime;
		ResultMove(_DeltaTime);
		if (GetActorLocation().Y >= 1500) {
			Destroy();
		}
		return true;
	}


	return false;
}

void Koopa::MonsterInit()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ {0,-64}, {100,128} });
}


void Koopa::CollisionEvent(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		UCollision* Collision = Result[0];
		Mario* Player = (Mario*)Collision->GetOwner();
		Player->Hit();
	}
	std::vector<UCollision*> MResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, MResult)) {
		GravitySpeed.Y = 0;
		SpeedY.Y = 0;
	}

}

void Koopa::ExcuteStart()
{
	if (HP > 0) {
		HP--;
		return;
	}
	BGMPlayer = UEngineSound::SoundPlay("Stomp.wav");
	GravitySpeed.Y = 0.f;
	SpeedX.X = 0.f;
	SpeedY.Y = -500.f;
	BodyCollision->Destroy();
	KoopaExcute = true;
}

void Koopa::Excute(float _DeltaTime)
{
}
