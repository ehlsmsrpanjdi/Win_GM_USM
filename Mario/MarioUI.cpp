#include "MarioUI.h"
#include "MarioHelper.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/ImageRenderer.h>


MarioUI::MarioUI()
{
}

MarioUI::~MarioUI()
{
}

void MarioUI::SetMarioScore()
{
	std::string Index = std::to_string(MarioHelper::MarioTotalScore);
	std::string Test;
	for (int i = 0; i < 6; ++i) {
		Test = Index.substr(i + 1,1);
		Test.append(".png");
		Test;
		ScoreUIArray[i]->SetImage(Test);
	}

}

void MarioUI::BeginPlay()
{
	AActor::BeginPlay();

	PlayerUIRenderer = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	PlayerUIRenderer->SetImage("UIBar.png");

	FVector UIScale = PlayerUIRenderer->GetImage()->GetScale();

	PlayerUIRenderer->SetTransform({ {300,-100}, {UIScale.iX() * 3, UIScale.iY() * 3} });
	PlayerUIRenderer->CameraEffectOff();

	for (int i = 0; i < 6; ++i) {
		std::string Index = std::to_string(i);
		ScoreUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		ScoreUIArray[i]->SetImage(Index + ".png");
		ScoreUIArray[i]->SetTransform({ {300,200 + i * 100}, {20,20} });
		ScoreUIArray[i]->CameraEffectOff();
	}
}

void MarioUI::Tick(float _DeltaTime)
{
	SetMarioScore();
}

