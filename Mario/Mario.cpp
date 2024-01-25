#include "Mario.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "Fire.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

Mario::Mario()
{
}

Mario::~Mario()
{
}

void Mario::BeginPlay()
{
	//{
	//	EngineTime NewTime;
	//	NewTime.TimeCheckStart();
	//	std::vector<int> NewInt;
	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		NewInt.push_back(i);
	//	}
	//	float Time = NewTime.TimeCheck();
	//	int a = 0;
	//}
	//{
	//	EngineTime NewTime;
	//	NewTime.TimeCheckStart();
	//	std::list<int> NewInt;
	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		NewInt.push_back(i);
	//	}
	//	float Time = NewTime.TimeCheck();
	//	int a = 0;
	//}



	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void Mario::Tick(float _DeltaTime)
{
	// 1초에 2번을 실행했다면
	// Tick과 Tick사의 시간은? 
	// 0.5초 일꺼다.

	// 1초에 100을 가야하는 애가 있다고 칩시다.
	// 0.5초에 몇픽셀씩 움직여야 하나요?
	// 100 * 0.5


	if (true == EngineInput::IsPress('A'))
	{
		FVector AddedSpeed = AccelerateX * -1 * _DeltaTime;
		AddSpeed(AddedSpeed);
	}

	if (true == EngineInput::IsPress('D'))
	{
		FVector AddedSpeed = AccelerateX * _DeltaTime;
		AddSpeed(AddedSpeed);
	}

	if (true == EngineInput::IsPress('W'))
	{
		FVector AddedSpeed = AccelerateY * -1 * _DeltaTime;
		AddSpeed(AddedSpeed);
	}


	if (true == EngineInput::IsPress('S'))
	{
		FVector AddedSpeed = AccelerateY * _DeltaTime;
		AddSpeed(AddedSpeed);
	}

	AddActorLocation(CurSpeed * _DeltaTime);

	if (true == EngineInput::IsDown('Q'))
	{
		AFire* NewFire= GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}