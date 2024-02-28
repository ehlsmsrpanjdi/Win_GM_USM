#include "PlayLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "CollisionActor.h"
#include "GreenTroopa.h"
#include "Plant.h"
#include "MarioBlock.h"
#include "MarioBrick.h"
#include "MushRoom.h"
#include "MarioUI.h"
#include "MonsterGoomba.h"
#include "Coin.h"
#include "Flag.h"
#include "ItemFlower.h"
#include "Fire.h"
#include "FireEnd.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}


void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewDir;

	NewDir.MoveParent();
	NewDir.Move("ContentsResources");
	NewDir.Move("Map");
	NewDir.Move("Stage1");



	std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
	Mario* TestMario;
	TestMario = this->SpawnActor<Mario>(2);
	TestMario->SetActorLocation({ 200,800 });

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(0);
	Map->SetCollisionActorImage(GetName());


	MarioUI* UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200 });

	MonsterGoomba* Goomba;
	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 1300, 830 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 2686, 830 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 3300, 830 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 3500, 830 });

	MarioBlock* itemblock;
	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 1050,650 });

	MarioBrick* brick;
	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 1300,650 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::MushRoom);
	itemblock->SetActorLocation({ 1364,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 1428,650 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 1428,400 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 1492,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 1556,650 });

	MarioBrick* Itembrick;
	Itembrick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	Itembrick->SetItemBlockDefault(3, ItemState::Coin, BlockState::ItemBrick);
	Itembrick->SetActorLocation({ 5050,650 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 5114,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5178,650 });


	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5256,400 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 5300, 300 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 5500, 300 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5320,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5384,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5448,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5512,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5576,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 5640,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 6000,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 6064,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 6128,400 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 6192,400 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 7000,650 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 7200, 800 });

	Goomba = SpawnActor<MonsterGoomba>(MarioRenderOrder::Monster);
	Goomba->SetActorLocation({ 7400, 800 });

	GreenTroopa* Green;
	Green = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	Green->SetActorLocation({ 7600,800 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::MushRoom);
	itemblock->SetActorLocation({ 7300,650 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::Coin);
	itemblock->SetActorLocation({ 7600,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 7800,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 7864,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 7928,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 8250,400 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(3, ItemState::Coin);
	itemblock->SetActorLocation({ 8314,400 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::MushRoom);
	itemblock->SetActorLocation({ 8378,400 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 8314,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 10800,650 });

	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 10864,650 });


	brick = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	brick->SetBrickDefault();
	brick->SetActorLocation({ 10928,650 });

	itemblock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	itemblock->SetItemBlockDefault(1, ItemState::MushRoom);
	itemblock->SetActorLocation({ 10992,650 });

	Flag* flag = SpawnActor<Flag>(MarioRenderOrder::Item);
	flag->SetActorLocation({ 12704.f, 490.f });
}

void UPlayLevel::Tick(float _DeltaTime)
{
}

void UPlayLevel::LevelStart(ULevel* Level)
{
	MarioHelper::SetPrevLevel("Stage1");
}
