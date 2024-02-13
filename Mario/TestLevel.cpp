#include "ContentsCore.h"
#include "TestLevel.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "TitleLogo.h"
#include "Goomba.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
	Goomba* TestMonster;
	TestMonster = this->SpawnActor<Goomba>(1);
	TestMonster->SetActorLocation({ 200, 200 });



}