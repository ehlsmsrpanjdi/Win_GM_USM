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
	if (MarioHelper::LevelEnd) {
		if (MarioHelper::MarioTime > 1000 && MinusTime < 0)
		{
			MarioHelper::MarioTime -= 1;
			MarioHelper::MarioTotalScore += 100;
			MinusTime = MinusTime + 0.004f;
		}
		else {
			MinusTime -= _DeltaTime;
		}
	}

	if (Time >= 1.f && MarioHelper::MarioTime > 1000 && !MarioHelper::LevelEnd) {
		Time = 0.f;
		MarioHelper::MarioTime -= 1;
	}
	else {
		Time += _DeltaTime;
	}

	std::string Index = std::to_string(MarioHelper::MarioTime);
	std::string str;
	for (int i = 0; i < 3; ++i) {
		str = Index.substr(i + 1, 1);
		str.append(".png");
		TimeUIArray[i]->SetImage(str);
	}

}

void MarioUI::SetMarioCoinUI()
{
	std::string Index = std::to_string(MarioHelper::MarioCoinCount);
	std::string str;
	for (int i = 0; i < 2; ++i) {
		str = Index.substr(i + 1, 1);
		str.append(".png");
		CoinUIArray[i]->SetImage(str);
	}
}

void MarioUI::SetMarioWorldUI()
{
	std::string Index = std::to_string(MarioHelper::MarioWorldCount);
	std::string str;
	for (int i = 0; i < 2; ++i) {
		str = Index.substr(i, 1);
		str.append(".png");
		WorldUIArray[i]->SetImage(str);
	}
}

void MarioUI::BeginPlay()
{
	AActor::BeginPlay();

	PlayerUIRenderer = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	PlayerUIRenderer->SetImage("UIBar.png");

	CoinImage = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	CoinImage->SetImage("Coin_Origin.PNG");
	CoinImage->SetTransform(CoinUITransform);

	CoinImage->CreateAnimation("Idle", "Coin_Origin.PNG", 0, 5, 0.2f, true);
	CoinImage->ChangeAnimation("Idle");
	CoinImage->CameraEffectOff();


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
		CoinUIArray[i]->SetTransform(CoinCountUITransform);
		CoinCountUITransform.AddPosition({ PlusSize,0 });
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
	SetMarioCoinUI();
	SetMarioWorldUI();
	SetMarioTimeUI(_DeltaTime);
	IsLevelEnd(_DeltaTime);
}

void MarioUI::IsLevelEnd(float _DeltaTime)
{
	if (MarioHelper::LevelEnd == true) {
		if (ChangeLevelTime >= 0) {
			ChangeLevelTime -= _DeltaTime;
		}
		else {
		MarioHelper::LevelEnd = false;
		ChangeLevelTime = 5.0f;
		GEngine->ChangeLevel("Loading");
		}

	}
}

