#include "Fire.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

AFire::AFire() {

}

AFire::~AFire()
{
}


void AFire::BeginPlay()
{
	UImageRenderer* Renderer = CreateImageRenderer(-10);
	Renderer->SetImageToScale("AAA.png");

	Destroy(2.0f);
}

void AFire::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}