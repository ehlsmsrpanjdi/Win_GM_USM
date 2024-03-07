#include "PlayLevel2.h"
#include "CollisionActor.h"
#include <EnginePlatform/EngineResources.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include "Mario.h"
#include "CameraOffCollisionActor.h"
#include "Stage2Pipe.h"
#include "GroundBrick.h"
#include "GroundBlock.h"

PlayLevel2::PlayLevel2() 
{
}

PlayLevel2::~PlayLevel2() 
{
}

void PlayLevel2::BeginPlay()
{
	ULevel::BeginPlay();

	if (!MarioHelper::StageOneInit) {
		MarioHelper::StageOneInit = true;
		UEngineDirectory NewDir;

		NewDir.MoveParent();
		NewDir.Move("ContentsResources");
		NewDir.Move("Map");
		NewDir.Move("Stage2");

		std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath();
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath);
		}
	}

	BackGroundMap* Map;
	Map = SpawnActor<BackGroundMap>(MarioRenderOrder::Map);
	Map->SetCollisionActorImage(GetName());

	Mario* TestMario;
	TestMario = SpawnActor<Mario>(MarioRenderOrder::Player);
	TestMario->SetActorLocation({ 200,1531 });
	SetCameraPos({ 0,960 });

	CameraOffCollisionActor* CameraBan;
	CameraBan = SpawnActor<CameraOffCollisionActor>();
	CameraBan->SetActorLocation({ 150,600 });

	Stage2Pipe* StartPipe;
	StartPipe = SpawnActor<Stage2Pipe>(MarioRenderOrder::Cheat);
	StartPipe->SetActorLocation({ 707,768 });
	StartPipe->SetTotalLocation({ 200,1060 }, { 0,960 });

	GroundBrick* GBrick;
	GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
	GBrick->SetActorLocation({ 400,1600 });

	GroundBlock* GIBlock;
	GIBlock = SpawnActor<GroundBlock>(MarioRenderOrder::Block);
	GIBlock->SetActorLocation({ 600,1600 });
	GIBlock->SetItemState(ItemState::Coin);

}

void PlayLevel2::Tick(float _DeltaTime)
{
}

void PlayLevel2::LevelStart(ULevel* Level)
{
}
