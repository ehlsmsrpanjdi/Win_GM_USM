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
	TestMario->SetActorLocation({ 200,200 });

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(0);
	Map->SetCollisionActorImage(GetName());


	MarioUI* TestUI;
	TestUI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	TestUI->SetActorLocation({ 200,200 });

	MushRoom* mush;
	mush = SpawnActor<MushRoom>(MarioRenderOrder::Item);
	mush->SetActorLocation({ 700,600 });

	Coin* co;
	co = SpawnActor<Coin>(MarioRenderOrder::Item);
	co->SetActorLocation({ 500,600 });

	Flag* block;
	block = SpawnActor<Flag>(MarioRenderOrder::Block);
	block->SetActorLocation({ 500,600 });

}

void UPlayLevel::Tick(float _DeltaTime)
{
}
