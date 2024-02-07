#include "EngineTime.h"
#include <Windows.h>

double EngineTime::TestTime;

EngineTime::EngineTime()
{
	TimeCheckStart();
}

EngineTime::~EngineTime()
{
}

void EngineTime::TimeCheckStart()
{
	// �ʴ� ���� �ִ� ���ε�.
	QueryPerformanceFrequency(&Count);

	QueryPerformanceCounter(&PrevTime);

	dCount = static_cast<double>(Count.QuadPart);
}

float EngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);
	TestTime = static_cast<double>(Tick);

	// ���е��� ���̱� ���ؼ� double�� ����Ѵ�.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}