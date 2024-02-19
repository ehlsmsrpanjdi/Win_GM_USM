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

	//Goomba* TestGoomba;
	//TestGoomba = SpawnActor<Goomba>(MarioRenderOrder::Monster);
	//TestGoomba->SetActorLocation({ 800,200 });

	GreenTroopa* TestTroopa;
	TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	TestTroopa->SetActorLocation({ 1000,200 });

	TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	TestTroopa->SetActorLocation({ 1200,200 });

	TestTroopa = SpawnActor<GreenTroopa>(MarioRenderOrder::Monster);
	TestTroopa->SetActorLocation({ 1400,200 });

	//MarioBlock* TestBlock;
	//TestBlock = SpawnActor<MarioBlock>(MarioRenderOrder::Block);
	//TestBlock->SetActorLocation({ 1000,200 });


	//Plant* TestPlant;
	//TestPlant = SpawnActor<Plant>(MarioRenderOrder::Monster);
	//TestPlant->StartLocation = { 600,600 };
	//TestPlant->SetActorLocation(TestPlant->StartLocation);
	

}

void UPlayLevel::Tick(float _DeltaTime)
{
}
