#include "ContentsCore.h"
#include "TitleLevel.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "TitleLogo.h"
#include "MarioHelper.h"
#include "MarioUI.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	UEngineDirectory NewDir;

	// D:\Project\GM\WIn
	NewDir.MoveParent();

	// D:\Project\GM\WIn\ContentsResources
	NewDir.Move("ContentsResources");
	NewDir.Move("Map");
	NewDir.Move("Title");
	std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);

	// 엔진만의 규칙을 정할거냐.
	for (UEngineFile& File : NewList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	SpawnActor<TitleLogo>();

}

void UTitleLevel::Tick(float _DeltaTime)
{
	if (UEngineInput::IsDown('U')) {
		GEngine->ChangeLevel("Stage1");
	}
}

