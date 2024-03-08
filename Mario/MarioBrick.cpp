#include "MarioBrick.h"
#include "BrokenBrick.h"
#include "GroundBrokenBrick.h"

MarioBrick::MarioBrick() 
{
	NoDir = true;
}

MarioBrick::~MarioBrick() 
{
	FVector CurLocation = GetActorLocation();

	if (CurLocation.X < GetWorld()->GetCameraPos().X) {
		return;
	}
	if (!IsGround) {
	BrokenBrick* Broken;
	Broken = GetWorld()->SpawnActor<BrokenBrick>(MarioRenderOrder::Block);
	Broken->SetActorLocation(FVector{ CurLocation.X - 16, CurLocation.Y - 64 });
	Broken->SetDirState(EActorDir::Left);

	Broken = GetWorld()->SpawnActor<BrokenBrick>(MarioRenderOrder::Block);
	Broken->SetActorLocation(FVector{ CurLocation.X - 16, CurLocation.Y });
	Broken->SetDirState(EActorDir::Left);

	Broken = GetWorld()->SpawnActor<BrokenBrick>(MarioRenderOrder::Block);
	Broken->SetActorLocation(FVector{ CurLocation.X + 16, CurLocation.Y - 64 });
	Broken->SetDirState(EActorDir::Right);

	Broken = GetWorld()->SpawnActor<BrokenBrick>(MarioRenderOrder::Block);
	Broken->SetActorLocation(FVector{ CurLocation.X + 16, CurLocation.Y });
	Broken->SetDirState(EActorDir::Right);
	}
	else {
		GroundBrokenBrick* Broken;
		Broken = GetWorld()->SpawnActor<GroundBrokenBrick>(MarioRenderOrder::Block);
		Broken->SetActorLocation(FVector{ CurLocation.X - 16, CurLocation.Y - 64 });
		Broken->SetDirState(EActorDir::Left);

		Broken = GetWorld()->SpawnActor<GroundBrokenBrick>(MarioRenderOrder::Block);
		Broken->SetActorLocation(FVector{ CurLocation.X - 16, CurLocation.Y });
		Broken->SetDirState(EActorDir::Left);

		Broken = GetWorld()->SpawnActor<GroundBrokenBrick>(MarioRenderOrder::Block);
		Broken->SetActorLocation(FVector{ CurLocation.X + 16, CurLocation.Y - 64 });
		Broken->SetDirState(EActorDir::Right);

		Broken = GetWorld()->SpawnActor<GroundBrokenBrick>(MarioRenderOrder::Block);
		Broken->SetActorLocation(FVector{ CurLocation.X + 16, CurLocation.Y });
		Broken->SetDirState(EActorDir::Right);
	}

}

void MarioBrick::BeginPlay()
{
	NoDir = true;
	StartState = BlockState::Brick;
	SetName("MarioBrick");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("MarioBrick.png");
	Renderer->SetTransform({ {0,0 }, { 256,256 } });
	AnimationAuto(Renderer, "Brick", 0, 0, 0.1f, false);
	SetAnimation("Brick");

	AnimationAuto(Renderer, "Default", 4, 4, 0.1f, false);
}

void MarioBrick::BlockInit()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });

	BoxState = BlockState::Brick;
	StartState = BlockState::Brick;
}



