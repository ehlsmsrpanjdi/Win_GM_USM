#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineWindow.h>
#include <Mario/ContentsCore.h>

// ���� �������� �����鿡�� ������ �⵿�� �����ϱ� ���ؼ� ����� ���.

// ����ڰ� �ϰ� �������� ��� ��� �����ϰ� ����ų�?
// ���� ������ ũ�⸦ �����ϰ� �;�.

// ENGINESTART(UContentExCore);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LeakCheck;
	ContentsCore NewUserCore = ContentsCore();
	NewUserCore.EngineStart(hInstance);
}