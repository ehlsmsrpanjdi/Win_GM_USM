#include "ContentsCore.h"
#include "Mario.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase\EngineFile.h>
#include "LoadingLevel.h"

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

	UEngineResourcesManager::GetInst().CuttingImage("Mario_Right.png", 5, 7);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Left.png", 5, 7);
	UEngineResourcesManager::GetInst().CuttingImage("Goomba.png", 3,1);
	UEngineResourcesManager::GetInst().CuttingImage("GreenTroopa_Left.png", 6, 1);
	UEngineResourcesManager::GetInst().CuttingImage("GreenTroopa_Right.png", 6, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Plant.png", 2, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MarioBlock.png", 6, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MarioBrick.png", 5, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Item.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Number_Origin.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Coin.png", 4, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Fire.png", 4, 1);
	UEngineResourcesManager::GetInst().CuttingImage("BrokenBrick.png", 2, 2);
	UEngineResourcesManager::GetInst().CuttingImage("FireEnd.png", 3, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Coin_Origin.png", 6, 1);

	

	MainWindow.SetWindowScale({ 256 * 4/* * 1.5f*/, 240 * 4/* * 1.5f*/ });
	MainWindow.SetWindowPosition({ 800/* * 1.5f*/, 0/* * 1.5f*/ });


	CreateLevel<UPlayLevel>("Stage1");
	CreateLevel<LoadingLevel>("Loading");
	CreateLevel<UTitleLevel>("Title");
	//ChangeLevel("Title");
	ChangeLevel("Title");
}

void ContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// 플레이어 움직여야 한다.
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void ContentsCore::End()
{
}