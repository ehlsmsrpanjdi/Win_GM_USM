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
	//// �����ΰ� ���;� �Ѵٰ� �����մϴ�.
	//UEngineDirectory NewPath;

	//NewPath.MoveParent();
	//// NewPath.Move("ContentsResources");

	//NewPath.Move("ContentsResources");
	//NewPath.Move("Texture");


	//// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
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
	


	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
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