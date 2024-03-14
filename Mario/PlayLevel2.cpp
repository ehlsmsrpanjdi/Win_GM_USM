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
#include "MovingBlock.h"
#include "PipeCheat.h"
#include "Pipe.h"
#include "Flag.h"
#include "Door.h"
#include "GreenTroopa.h"
#include "Plant.h"
#include "PipePlant.h"
#include "SoundCheat.h"


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
	TestMario->SetActorLocation({ 200,831 });

	PipeCheat* CheatPipe;
	CheatPipe = SpawnActor<PipeCheat>(MarioRenderOrder::Cheat);
	CheatPipe->SetActorLocation({ 7040,1600 });

	Plant* PP;
	PP = SpawnActor<Plant>(MarioRenderOrder::Monster);
	PP->SetActorLocation({ 6655,1600 });

	PP = SpawnActor<Plant>(MarioRenderOrder::Monster);
	PP->SetActorLocation({ 7040,1536});

	PipePlant* PPP;
	PPP = SpawnActor<PipePlant>(MarioRenderOrder::Monster);
	PPP->SetActorLocation({ 10305, 802});

	MovingBlock* MBlock;
	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 9042,836 });
	MBlock->MovingBlockInit({ 9042,836 }, { 9042,2048 }, true);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 9042,1236 });
	MBlock->MovingBlockInit({ 9042,836 }, { 9042,2048 }, true);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 9042,1636 });
	MBlock->MovingBlockInit({ 9042,836 }, { 9042,2048 }, true);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 10000,2048 });
	MBlock->MovingBlockInit({ 10000,2048 }, { 10000,1024 }, true);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 10000,1706 });
	MBlock->MovingBlockInit({ 10000,2048 }, { 10000,1024 }, true);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 10000,1365 });
	MBlock->MovingBlockInit({ 10000,2048 }, { 10000,1024 }, true);

	CameraOffCollisionActor* CameraBan;
	CameraBan = SpawnActor<CameraOffCollisionActor>();
	CameraBan->SetActorLocation({ 150,600 });

	Stage2Pipe* StartPipe;
	StartPipe = SpawnActor<Stage2Pipe>(MarioRenderOrder::Cheat);
	StartPipe->SetActorLocation({ 707,768 });
	StartPipe->SetTotalLocation({ 200,1060 }, { 0,960 });

	LeftPipe* EndPipe;
	EndPipe = SpawnActor<LeftPipe>(MarioRenderOrder::Cheat);
	EndPipe->SetActorLocation({ 10688,1536 });
	EndPipe->SetTotalLocation({ 10305,831 }, { 10050,0 });

	EndPipe = SpawnActor<LeftPipe>(MarioRenderOrder::Cheat);
	EndPipe->SetActorLocation({ 7040,2688 });
	EndPipe->SetTotalLocation({ 7422,1792 }, { 7120,960 });

	Pipe* GroundPipe;
	GroundPipe = SpawnActor<Pipe>(MarioRenderOrder::Cheat);
	GroundPipe->SetActorLocation({ 6656,1664 });
	GroundPipe->SetTotalLocation({ 6276,2280 }, { 6145,1920 });


	CheatPipe = SpawnActor<PipeCheat>(MarioRenderOrder::Cheat);
	CheatPipe->SetActorLocation({ 10304,768 });

	CheatPipe = SpawnActor<PipeCheat>(MarioRenderOrder::Cheat);
	CheatPipe->SetActorLocation({ 7424,1728 });

	GroundBlock* GIBlock;

	GIBlock = SpawnActor<GroundBlock>(MarioRenderOrder::Block);
	GIBlock->SetActorLocation({ 674,1600 });
	GIBlock->SetItemBlockDefault(1, ItemState::MushRoom);

	for (int i = 0; i < 5; ++i) {
		GIBlock = SpawnActor<GroundBlock>(MarioRenderOrder::Block);
		GIBlock->SetActorLocation({ 738 + i * 64,1600 });
		GIBlock->SetItemBlockDefault();
	}

	GroundGoomba* Goom;
	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 1000,1791 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 924,1791 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 1940,1791 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 5088,1530 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 5002,1530 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 6524,1786 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 6448,1786 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 6384,1786 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 8712,1529 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 8800,1529 });

	GreenTroopa* GT;
	GT = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	GT->SetActorLocation({ 3193, 1791 });

	GT = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	GT->SetActorLocation({ 3100, 1791 });

	GT = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	GT->SetActorLocation({ 3770, 1791 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 3950,1791 });

	Goom = SpawnActor<GroundGoomba>(MarioRenderOrder::Monster);
	Goom->SetActorLocation({ 4100,1791 });

	GroundBrick* GBrick;
	GroundCoin* GCoin;

	for (int i = 0; i < 10; ++i) {
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 6370 + i * 64, 2528 });
		GBrick->SetBrickDefault();
	}

	for (int i = 0; i < 8; ++i) {
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 6442 + i * 64, 2464 });
	}

	for (int i = 0; i < 10; ++i) {
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 6378 + i * 64, 2720 });
	}

	GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
	GBrick->SetActorLocation({ 1890, 1536 });
	GBrick->SetItemBrickDefault(1, ItemState::MushRoom, BlockState::ItemBrick);

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
			GBrick->SetActorLocation({ 4125 + j * 64, 1344 + i * 64 });
			GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 3; ++i) {
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
		GBrick->SetActorLocation({ 4573 + i * 64, 1728 });
		GBrick->SetBrickDefault();
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
			GBrick->SetActorLocation({ 5540 + i * 64, 1472 + j * 64 });
			GBrick->SetBrickDefault();
		}
	}

	for (int i = 0; i < 4; ++i) {
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 5540 + i * 64,1344 });
	}

	for (int i = 0; i < 6; ++i) {
		GBrick = SpawnActor<GroundBrick>(MarioRenderOrder::Block);
		GBrick->SetActorLocation({ 9305 + i * 64, 1536 });
		GBrick->SetBrickDefault();
	}

	Flag* EndFlag;
	EndFlag = SpawnActor<Flag>(MarioRenderOrder::Block);
	EndFlag->SetActorLocation({ 11488,487 });

	Door* EndDoor;
	EndDoor = SpawnActor<Door>(MarioRenderOrder::Item);
	EndDoor->SetActorLocation({ 11738,490 });
	EndDoor->DoorNextLevel("Stage3");

	CameraBan = SpawnActor<CameraOffCollisionActor>(MarioRenderOrder::Item);
	CameraBan->SetActorLocation({ 11658,831 });
	StartBGMPlayer = UEngineSound::SoundPlay("Level2Start.mp3");
	GroundBGMPlayer = UEngineSound::SoundPlay("Level2.mp3");
	GroundBGMPlayer.Off();
	GroundBGMPlayer.SetVolume(0.7f);
	BGMPlayer = UEngineSound::SoundPlay("Level1.mp3");
	BGMPlayer.Off();
	BGMPlayer.SetVolume(0.7f);

	SoundCheat* CheatSound = SpawnActor<SoundCheat>(MarioRenderOrder::Cheat);
	CheatSound->SetActorLocation({ 10308,704 });
	CheatSound->SetBool(false);
}



void PlayLevel2::Tick(float _DeltaTime)
{
	if (MarioHelper::SoundOff) {
		GroundBGMPlayer.Off();
		BGMPlayer.Off();
		return;
	}

	if (Level2SoundTime >= 0) {
	Level2SoundTime -= _DeltaTime;
	}
	else if(!SoundStart){
		GroundBGMPlayer.On();
		SoundStart = true;
	}

	if (MarioHelper::Stage2Sound) {

	}
	else {
		GroundBGMPlayer.Off();
		BGMPlayer.On();
	}

}

void PlayLevel2::LevelStart(ULevel* Level)
{
	MarioHelper::SetPrevLevel("Stage2");
	Level2SoundTime = 6.0f;
	BGMPlayer.Off();
}

void PlayLevel2::LevelEnd(ULevel* Level)
{
	GroundBGMPlayer.Off();
	BGMPlayer.Off();
}
