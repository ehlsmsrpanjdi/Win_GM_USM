#include "ContentsCore.h"
#include "Mario.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase\EngineFile.h>
#include "TestLevel.h"

ContentsCore::ContentsCore()
	: UEngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ���ӽ���
void ContentsCore::BeginPlay()
{

	UEngineCore::BeginPlay();
	UEngineDirectory NewDir;

	NewDir.MoveParent();

	NewDir.Move("ContentsResources");
	NewDir.Move("Global");

	std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);

	// �������� ��Ģ�� ���Ұų�.
	for (UEngineFile& File : NewList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("Mario_Right.png", 5, 8);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Left.png", 5, 8);
	UEngineResourcesManager::GetInst().CuttingImage("Goomba.png", 3,1);
	UEngineResourcesManager::GetInst().CuttingImage("GreenTroopa_Left.png", 6, 1);
	UEngineResourcesManager::GetInst().CuttingImage("GreenTroopa_Right.png", 6, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Plant.png", 2, 1);

	MainWindow.SetWindowScale({ 256 * 4/* * 1.5f*/, 240 * 4/* * 1.5f*/ });
	MainWindow.SetWindowPosition({ 800/* * 1.5f*/, 0/* * 1.5f*/ });


	CreateLevel<UPlayLevel>("Stage1");
	ChangeLevel("Stage1");
}

void ContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// �÷��̾� �������� �Ѵ�.
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void ContentsCore::End()
{
}