#include "PlayLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "CollisionActor.h"

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
	BackGroundMap* Map;
	TestMario = this->SpawnActor<Mario>();
	Map = this->SpawnActor<BackGroundMap>();
	Map->SetCollisionActorImage(GetName());
	TestMario->SetActorLocation({ 200,200 });

}

void UPlayLevel::Tick(float _DeltaTime)
{
}
