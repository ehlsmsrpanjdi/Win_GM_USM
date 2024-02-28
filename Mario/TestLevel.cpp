#include "ContentsCore.h"
#include "TestLevel.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "TitleLogo.h"
#include "GreenTroopa.h"
#include "PhysicsActor.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{

	GreenTroopa* TestMonster2;
	TestMonster2 = this->SpawnActor<GreenTroopa>(1);
	TestMonster2->SetActorLocation({ 200,300 });

}


