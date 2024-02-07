#include "ContentsCore.h"
#include "Mario.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase\EngineFile.h>

ContentsCore::ContentsCore()
	: UEngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 게임시작
void ContentsCore::BeginPlay()
{

	UEngineCore::BeginPlay();
	UEngineDirectory NewDir;

	NewDir.MoveParent();

	NewDir.Move("ContentsResources");
	NewDir.Move("Global");

	std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);

	// 엔진만의 규칙을 정할거냐.
	for (UEngineFile& File : NewList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("TestPlayer_Right.png", 5, 8);
	UEngineResourcesManager::GetInst().CuttingImage("TestPlayer_Left.png", 5, 8);

	MainWindow.SetWindowScale({ 256 * 4/* * 1.5f*/, 240 * 4/* * 1.5f*/ });
	MainWindow.SetWindowPosition({ 800/* * 1.5f*/, 0/* * 1.5f*/ });
	// 1200 
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("Stage1");
	ChangeLevel("Stage1");
}

void ContentsCore::Tick(float _DeltaTime)
{
	// 플레이어 움직여야 한다.
}

void ContentsCore::End()
{
}