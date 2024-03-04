#include "LastLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "MarioBlock.h"
#include "MarioBrick.h"
#include "MarioUI.h"
#include "Koopa.h"
#include "KoopaFire.h"
#include "CollisionActor.h"
#include "FireWall.h"

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

		NewDir.MoveParent();
		NewDir.Move("ContentsResources");
		NewDir.Move("Map");
		NewDir.Move("LastStage");

		std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath();
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath);
		}
	}
	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>(0);
	Map->SetCollisionActorImage(GetName());
	
	Mario* TestMario;
	TestMario = this->SpawnActor<Mario>(2);
	TestMario->SetActorLocation({ 100,440 });

	MarioUI* UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200 });

	FireWall* wall = SpawnActor<FireWall>(MarioRenderOrder::Monster);
	wall->SetActorLocation({ 400,500 });
	

}

void LastLevel::Tick(float _DeltaTime)
{
}

void LastLevel::LevelStart(ULevel* Level)
{
	MarioHelper::SetPrevLevel("LastStage");
}
