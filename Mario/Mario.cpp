#include "Mario.h"
#include <EngineCore\EngineCore.h>

Mario::Mario()
{
}

Mario::~Mario()
{
}

void Mario::BeginPlay()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void Mario::Tick(float _DeltaTime)
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();

	FVector Pos = GetActorLocation();
	Pos.X += 1;
	SetActorLocation(Pos);

	FTransform Trans = GetTransform();




	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}