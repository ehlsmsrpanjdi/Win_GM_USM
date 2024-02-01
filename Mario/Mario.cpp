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
	AActor::BeginPlay();
	SetActorLocation({ 100, 100 });

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
	else {

	}

	if (true == EngineInput::IsPress('D'))
	{
		FVector AddedSpeed = AccelerateX * _DeltaTime;
		AddSpeed(AddedSpeed);
	}
	else {

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

	if (true == EngineInput::IsPress('T'))
	{
		GEngine->End();
	}



	AddActorLocation(CurSpeed * _DeltaTime);

	if (true == EngineInput::IsDown('Q'))
	{
		AFire* NewFire= GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}
}

void Mario::AddSpeed(FVector _FVector) {

	if (MaxSpeedX >= CurSpeed.X + _FVector.X && -MaxSpeedX <= CurSpeed.X + _FVector.X) {
		CurSpeed.X += _FVector.X;
	}

	if (MaxSpeedY >= CurSpeed.Y + _FVector.Y && -MaxSpeedY <= CurSpeed.Y + _FVector.Y) {
		CurSpeed.Y += _FVector.Y;
	}
}