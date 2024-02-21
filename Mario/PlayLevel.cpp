#include "PlayLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "CollisionActor.h"
#include "Goomba.h"
#include "GreenTroopa.h"
#include "Plant.h"
#include "MarioBlock.h"
#include "MarioBrick.h"
#include "MushRoom.h"

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

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(0);
	Map->SetCollisionActorImage(GetName());

	TestMario->SetActorLocation({ 200,200 });

	//MushRoom* TestItem;
	//TestItem = SpawnActor<MushRoom>(MarioRenderOrder::Item);
	//TestItem->SetActorLocation({ 800,200 });

	//Goomba* TestGoomba;
	//TestGoomba = SpawnActor<Goomba>(MarioRenderOrder::Monster);
	//TestGoomba->SetActorLocation({ 600,200 });


	//TestGoomba = SpawnActor<Goomba>(MarioRenderOrder::Monster);
	//TestGoomba->SetActorLocation({ 800,200 });


	//TestGoomba = SpawnActor<Goomba>(MarioRenderOrder::Monster);
	//TestGoomba->SetActorLocation({ 900,200 });

	//GreenTroopa* TestTroopa;
	//TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	//TestTroopa->SetActorLocation({ 1000,200 });

	//TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	//TestTroopa->SetActorLocation({ 1200,200 });

	//TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	//TestTroopa->SetActorLocation({ 1400,200 });

	MarioBlock* TestBlock;

	TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	TestBlock->SetActorLocation({ 864,600 });

	TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	TestBlock->SetActorLocation({ 940,600 });

	TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	TestBlock->SetActorLocation({ 1100,600 });

	//TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	//TestBlock->SetActorLocation({ 928,600 });

	//TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	//TestBlock->SetActorLocation({ 992,600 });

	TestBlock = SpawnActor<MarioBrick>(MarioRenderOrder::Block);
	TestBlock->SetActorLocation({ 1300,600 });

	
	Plant* TestPlant;
	TestPlant = SpawnActor<Plant>(MarioRenderOrder::Monster);
	TestPlant->SetActorLocation({ 600,600 });
	
	TestPlant = SpawnActor<Plant>(MarioRenderOrder::Monster);
	TestPlant->SetActorLocation({ 700,600 });

	TestPlant = SpawnActor<Plant>(MarioRenderOrder::Monster);
	TestPlant->SetActorLocation({ 800,600 });

}

void UPlayLevel::Tick(float _DeltaTime)
{
}
