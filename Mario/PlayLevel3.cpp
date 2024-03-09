#include "PlayLevel3.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "CollisionActor.h"
#include "MarioBlock.h"
#include "MarioBrick.h"
#include "GroundCoin.h"
#include "MovingBlock.h"
#include "RedTroopa.h"
#include "Flag.h"
#include "Door.h"
#include "CameraOffCollisionActor.h"
#include "MonsterGoomba.h"

PlayLevel3::PlayLevel3()
{
}

PlayLevel3::~PlayLevel3()
{
}

void PlayLevel3::BeginPlay()
{
	ULevel::BeginPlay();

	if (!MarioHelper::StageThreeInit) {
		MarioHelper::StageThreeInit = true;
		UEngineDirectory NewDir;

		NewDir.MoveParent();
		NewDir.Move("ContentsResources");
		NewDir.Move("Map");
		NewDir.Move("Stage3");

		std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath();
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath);
		}
	}

	Mario* TestMario;
	TestMario = this->SpawnActor<Mario>(MarioRenderOrder::Player);
	TestMario->SetActorLocation({ 200,800 });

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(MarioRenderOrder::Map);
	Map->SetCollisionActorImage(GetName());

	MarioUI* UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200 });

	GroundCoin* GCoin;
	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 1760,320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 1824,320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 1890,320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 2140,767 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 2395,192 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 2459,192 });


	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 3232,447 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 3296, 447 });

	for (int i = 0; i < 4; ++i) {
		GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
		GCoin->SetActorLocation({ 3870 + i * 64, 319 });
	}

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 5473, 389 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 5537, 389 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 5973, 320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 6037, 320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 6293, 320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 6357, 320 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 7260, 833 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 7324, 833 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 7388, 833 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 7710, 391 });

	GCoin = SpawnActor<GroundCoin>(MarioRenderOrder::Item);
	GCoin->SetActorLocation({ 7774, 391 });

	MovingBlock* MBlock;
	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 3616,422 });
	MBlock->MovingBlockInit({ 3616,422 }, { 3616,806 }, false);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 5390,548 });
	MBlock->MovingBlockInit({ 5390,548 }, { 5760,548 }, false);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 5860,606 });
	MBlock->MovingBlockInit({ 5860,606 }, { 6206,606 }, false);

	MBlock = SpawnActor<MovingBlock>(MarioRenderOrder::Block);
	MBlock->SetActorLocation({ 8213,429 });
	MBlock->MovingBlockInit({ 8213,429 }, { 8692,429 }, false);

	RedTroopa* Red;
	Red = SpawnActor<RedTroopa>(MarioRenderOrder::Monster);
	Red->SetActorLocation({ 1900,316 });

	Red = SpawnActor<RedTroopa>(MarioRenderOrder::Monster);
	Red->SetActorLocation({ 4771,264 });
	Red->FlyInit({ 4771,364 }, { 4771,723 });
	Red->SetMonsterState(MonsterState::Fly);

	Red = SpawnActor<RedTroopa>(MarioRenderOrder::Monster);
	Red->SetActorLocation({ 7057,447});

	Red = SpawnActor<RedTroopa>(MarioRenderOrder::Monster);
	Red->SetActorLocation({ 7320,250});
	Red->FlyInit({ 7320,250}, { 7320,600 });
	Red->SetMonsterState(MonsterState::Fly);

	MonsterGoomba* Goomba;
	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 2777,250 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 2914,250 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 5173,383 });

	MarioBlock* Block;
	Block = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	Block->SetItemBlockDefault(1, ItemState::MushRoom);

	Flag* EndFlag;
	EndFlag = SpawnActor<Flag>(MarioRenderOrder::Item);
	EndFlag->SetActorLocation({ 9760,490 });

	CameraOffCollisionActor* BanCamera = SpawnActor<CameraOffCollisionActor>(MarioRenderOrder::UI);
	BanCamera->SetActorLocation({ 9980,800 });

	Door* door = SpawnActor<Door>(MarioRenderOrder::UI);
	door->SetActorLocation({ 10050, 490 });
	door->DoorNextLevel("LastStage");

}

void PlayLevel3::Tick(float _DeltaTime)
{
}

void PlayLevel3::LevelStart(ULevel* Level)
{
}
