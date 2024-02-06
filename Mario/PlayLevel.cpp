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
	//// 실행경로가 나와야 한다고 생각합니다.
	//UEngineDirectory NewPath;

	//NewPath.MoveParent();
	//// NewPath.Move("ContentsResources");

	//NewPath.Move("ContentsResources");
	//NewPath.Move("Texture");


	//// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	//std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	//// CherryBomb_0.png
	//UEngineResourcesManager::GetInst().LoadImg("C:\\GM\\Win\\ContentsResources\\AAAA.png");

	//// ULevel* const This = this;

	UEngineDirectory NewDir;

	// NewPath.Move("ContentsResources");
	NewDir.MoveParent();
	NewDir.Move("ContentsResources");
	NewDir.Move("Map");
	NewDir.Move("Stage1");
	


	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
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
	//Map->SetCollisionActorImage(GetName());
	Map->SetRenderImage(GetName() + ".PNG");
	Map->SetColRenderImage(GetName() + "_Col.PNG");
	TestMario->SetActorLocation({ 200,200 });

}