#include "LastLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "MarioBlock.h"
#include "MarioBrick.h"
#include "MarioUI.h"
#include "Koopa.h"
#include "CollisionActor.h"
#include "FireWall.h"
#include "Flat.h"
#include "Koopa.h"
#include "EndingMessage.h"
#include "MarioBlock.h"
#include "CameraOffCollisionActor.h"
#include "MovingBlock.h"
#include "TrapFire.h"

LastLevel::LastLevel() 
{
}

LastLevel::~LastLevel() 
{
}

void LastLevel::BeginPlay()
{
	ULevel::BeginPlay();

	if (!MarioHelper::LastStageInit) {
		MarioHelper::LastStageInit = true;
		UEngineDirectory NewDir;

		NewDir.MoveToSearchChild("ContentsResources");
		NewDir.MoveToSearchChild("Map");
		NewDir.MoveToSearchChild("LastStage");

		std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath();
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath);
		}
	}
	TrapFire* TF;
	TF = SpawnActor<TrapFire>(MarioRenderOrder::Monster);
	TF->SetActorLocation({ 6247,500 });

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(0);
	Map->SetCollisionActorImage(GetName());
	
	Mario* TestMario;
	TestMario = this->SpawnActor<Mario>(2);
	TestMario->SetActorLocation({ 200,440 });


	Flat* Flats = SpawnActor<Flat>(MarioRenderOrder::Cheat);
	Flats->SetActorLocation({ 8224,672 });

	MarioUI* UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200});

	EndingMessage* Message = SpawnActor<EndingMessage>(MarioRenderOrder::UI);
	Message->SetActorLocation({ 9728,400 });

	MarioBlock* ItemBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	ItemBlock->SetActorLocation({ 1951, 464 });
	ItemBlock->SetItemBlockDefault(1, ItemState::MushRoom);

	FireWall* wall;

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 1952,677});


	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 3170,422 });

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 3872,422 });

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 4320,422 });

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 4895,615});

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 5407,615 });

	wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 5663,293 });
	
	Koopa* Boss = SpawnActor<Koopa>(MarioRenderOrder::Monster);
	Boss->SetActorLocation({ 8800,615 });

	CameraOffCollisionActor* BanCamera = SpawnActor<CameraOffCollisionActor>(MarioRenderOrder::UI);
	BanCamera->SetActorLocation({ 8700.f,800.f });

	MovingBlock* MB;
	MB = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MB->SetActorLocation({ 8800,400 });
	MB->MovingBlockInit({ 8400,400 }, { 8800,400 }, false);
	BGMPlayer = UEngineSound::SoundPlay("LastStage.mp3");
	BGMPlayer.SetVolume(0.7f);
}

void LastLevel::Tick(float _DeltaTime)
{
	if (MarioHelper::SoundOff) {
		BGMPlayer.Off();
		return;
	}
	if (MarioHelper::GameEnd) {
		BGMPlayer.Off();
		return;
	}
}

void LastLevel::LevelStart(ULevel* Level)
{
	MarioHelper::SetPrevLevel("LastStage");
}

void LastLevel::LevelEnd(ULevel* Level)
{
	BGMPlayer.Off();
	MarioHelper::GameEnd = false;
}
