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

void MarioUI::SetMarioScoreUI()
{
	std::string Index = std::to_string(MarioHelper::MarioTotalScore);
	std::string str;
	for (int i = 0; i < 6; ++i) {
		str = Index.substr(i + 1, 1);
		str.append(".png");
		ScoreUIArray[i]->SetImage(str);
	}

}

void MarioUI::SetMarioTimeUI(float _DeltaTime)
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

void MarioUI::SetMarioCoinUI()
{
}

void MarioUI::SetMarioWorldUI()
{
}

void MarioUI::BeginPlay()
{
	AActor::BeginPlay();

	PlayerUIRenderer = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	PlayerUIRenderer->SetImage("UIBar.png");

	FVector UIScale = PlayerUIRenderer->GetImage()->GetScale();

	PlayerUIRenderer->SetTransform(MainUITransform);
	PlayerUIRenderer->CameraEffectOff();

	for (int i = 0; i < 6; ++i) {
		std::string Index = std::to_string(i);
		ScoreUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		ScoreUIArray[i]->SetImage(Index + ".png");
		ScoreUIArray[i]->SetTransform(ScoreUITransform);
		ScoreUITransform.AddPosition({ PlusSize,0 });
		ScoreUIArray[i]->CameraEffectOff();
	}

	for (int i = 0; i < 2; ++i) {
		std::string Index = std::to_string(i);
		CoinUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		CoinUIArray[i]->SetImage(Index + ".png");
		CoinUIArray[i]->SetTransform(CoinUITransform);
		CoinUITransform.AddPosition({ PlusSize,0 });
		CoinUIArray[i]->CameraEffectOff();
	}

	for (int i = 0; i < 2; ++i) {
		std::string Index = std::to_string(i);
		WorldUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		WorldUIArray[i]->SetImage(Index + ".png");
		WorldUIArray[i]->SetTransform(WorldUITransform);
		WorldUITransform.AddPosition({ 55,0 });
		WorldUIArray[i]->CameraEffectOff();
	}

	for (int i = 0; i < 3; ++i) {
		std::string Index = std::to_string(i);
		TimeUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		TimeUIArray[i]->SetImage(Index + ".png");
		TimeUIArray[i]->SetTransform(TimeUITransform);
		TimeUITransform.AddPosition({ PlusSize,0 });
		TimeUIArray[i]->CameraEffectOff();
	}

}

void MarioUI::Tick(float _DeltaTime)
{
	//if (UEngineInput::IsDown(VK_DOWN)) {
	//	FVector A = PlayerUIRenderer->GetTransform().GetPosition();
	//	A.Y -= 1;
	//	PlayerUIRenderer->SetTransform({ {A},{1024,108} });
	//}
	//if (UEngineInput::IsDown(VK_UP)) {
	//	FVector A = PlayerUIRenderer->GetTransform().GetPosition();
	//	A.Y += 1;
	//	PlayerUIRenderer->SetTransform({ {A},{1024,108} });
	//}
	SetMarioScoreUI();
	SetMarioTimeUI(_DeltaTime);
}

