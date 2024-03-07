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
#include "GroundGoomba.h"
#include "MarioUI.h"

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
	
	MarioUI* UI;
	UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200 });

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

	GroundBlock* GIBlock;
	for (int i = 0; i < 5; ++i) {
	GIBlock = SpawnActor<GroundBlock>(MarioRenderOrder::Block);
	GIBlock->SetActorLocation({ 674 + i * 64,1600 });
	GIBlock->SetItemBlockDefault();
	}

	GroundBrick* GBrick;

	GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
	GBrick->SetActorLocation({ 1890, 1536 });
	GBrick->SetBrickDefault();

	{
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2526, 1472 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1472 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2718, 1472 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2782, 1472 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1472 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1472 });
		GBrick->SetBrickDefault();
	}

	{
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2526, 1536 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1536 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1536 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1536 });
		GBrick->SetBrickDefault();
	}

	{
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2526, 1600 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2590, 1600 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1600 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1600 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2910, 1600 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1600 });
		GBrick->SetBrickDefault();
	}

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 3485 + i * 64, 1408 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 3613 + i * 64, 1344 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 3613 + i * 64, 1600 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}

}



void PlayLevel2::Tick(float _DeltaTime)
{
}

void PlayLevel2::LevelStart(ULevel* Level)
{
}
