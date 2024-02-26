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
	std::string str;
	for (int i = 0; i < 6; ++i) {
		str = Index.substr(i + 1,1);
		str.append(".png");
		ScoreUIArray[i]->SetImage(str);
	}

}

void MarioUI::SetMarioTime(float _DeltaTime)
{
	if (Time >= 1.f) {
		Time = 0.f;
		MarioHelper::MarioTime -= 1;
	}
	else {
		Time += _DeltaTime;
	}
	
	std::string Index = std::to_string(MarioHelper::MarioTime);
	std::string str;
	for (int i = 0; i < 3; ++i) {
		str = Index.substr(i, 1);
		str.append(".png");
		TimeUIArray[i]->SetImage(str);
	}

}

void MarioUI::BeginPlay()
{
	AActor::BeginPlay();

	PlayerUIRenderer = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	PlayerUIRenderer->SetImage("UIBar.png");

	FVector UIScale = PlayerUIRenderer->GetImage()->GetScale();

	PlayerUIRenderer->SetTransform({ {300,-100}, {UIScale.iX() * 4, UIScale.iY() * 4} });
	PlayerUIRenderer->CameraEffectOff();

	for (int i = 0; i < 6; ++i) {
		std::string Index = std::to_string(i);
		ScoreUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		ScoreUIArray[i]->SetImage(Index + ".png");
		ScoreUIArray[i]->SetTransform({ {-120 + 35 * i,-50}, {20,20} });
		ScoreUIArray[i]->CameraEffectOff();
	}

	for (int i = 0; i < 3; ++i) {
		std::string Index = std::to_string(i);
		TimeUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		TimeUIArray[i]->SetImage(Index + ".png");
		TimeUIArray[i]->SetTransform({ {650 + i * 35, -50}, {20,20} });
		TimeUIArray[i]->CameraEffectOff();
	}
}

void MarioUI::Tick(float _DeltaTime)
{
	SetMarioScore();
	SetMarioTime(_DeltaTime);
}

