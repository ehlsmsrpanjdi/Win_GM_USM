#include "ContentsCore.h"
#include "Mario.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

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
	SetFrame(60);
	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";
	// 800 / 600�� �ʹ� ����.
	// MainWindow.SetWindowScale({1280, 720});

	// �߿��Ѱ� ũ�Ⱑ �ƴ϶� ����
	//MainWindow.SetWindowPosition({500, 100});
	//                           1024                960
	MainWindow.SetWindowScale({ 256 * 4/* * 1.5f*/, 240 * 4/* * 1.5f*/ });
	MainWindow.SetWindowPosition({ 800/* * 1.5f*/, 0/* * 1.5f*/ });
	// 1200 
	CreateLevel<UTitleLevel>("TitleLevel");

	ChangeLevel("TitleLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void ContentsCore::End()
{
}