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
#include "GroundCoin.h"

PlayLevel2::PlayLevel2()
{
}

PlayLevel2::~PlayLevel2()
{
}

void PlayLevel2::BeginPlay()
{
	ULevel::BeginPlay();

	if (!MarioHelper::StageTwoInit) {
		MarioHelper::StageTwoInit = true;
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
		GBrick->SetActorLocation({ 2526, 1432 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1432 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2718, 1432 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2782, 1432 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1432 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1432 });
		GBrick->SetBrickDefault();
	}

	{
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2526, 1496 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1496 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1496 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1496 });
		GBrick->SetBrickDefault();
	}

	{
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2526, 1560 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2590, 1560 });
		GBrick->SetBrickDefault();

		GroundCoin* GCoin;
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 2590,1496 });

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2654, 1560 });
		GBrick->SetBrickDefault();

		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 2590, 1624 });

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2846, 1560 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2910, 1560 });
		GBrick->SetBrickDefault();

		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 2974, 1560 });
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
			GBrick->SetActorLocation({ 3613 + i * 64, 1280 + j * 64 });
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

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 3869 + i * 64, 1216 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}
	GroundCoin* GCoin;
	for (int i = 0; i < 4; ++i) {
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 3869 + i * 64,1536 });
	}

	for (int i = 0; i < 6; ++i) {
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 3869 + i * 64, 1600 });
		GBrick->SetBrickDefault();
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 4125 + j * 64, 1344 + i * 64});
			GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 4381 + j * 64, 1408 + i * 64 });
			GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 4573 + i * 64, 1280 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 4; ++i) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 4573 + i * 64, 1728});
			GBrick->SetBrickDefault();
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 5540 + i * 64, 1472 + j * 64});
		GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 4; ++i) {
			GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
			GCoin->SetActorLocation({ 5540 + i * 64,1344 });
	}

	for (int i = 0; i < 6; ++i) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 9305 + i * 64, 1536});
			GBrick->SetBrickDefault();
	}


}



void PlayLevel2::Tick(float _DeltaTime)
{
}

void PlayLevel2::LevelStart(ULevel* Level)
{
}
