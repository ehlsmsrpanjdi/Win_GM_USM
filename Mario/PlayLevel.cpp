#include "PlayLevel.h"
#include "Mario.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "CollisionActor.h"
#include "Goomba.h"

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
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
	Mario* TestMario;
	TestMario = this->SpawnActor<Mario>();

	Goomba* TestMonster;
	TestMonster = this->SpawnActor<Goomba>();

	BackGroundMap* Map;
	Map = this->SpawnActor<BackGroundMap>();
	Map->SetCollisionActorImage(GetName());

	TestMario->SetActorLocation({ 200,200 });
	TestMonster->SetActorLocation({ 400,400 });


}

void UPlayLevel::Tick(float _DeltaTime)
{
}
