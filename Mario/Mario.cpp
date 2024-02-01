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
	// 1�ʿ� 2���� �����ߴٸ�
	// Tick�� Tick���� �ð���? 
	// 0.5�� �ϲ���.

	// 1�ʿ� 100�� �����ϴ� �ְ� �ִٰ� Ĩ�ô�.
	// 0.5�ʿ� ���ȼ��� �������� �ϳ���?
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