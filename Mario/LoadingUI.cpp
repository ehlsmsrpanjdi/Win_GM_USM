#include "LoadingUI.h"
#include "MarioHelper.h"

LoadingUI::LoadingUI()
{
}

LoadingUI::~LoadingUI()
{
}

void LoadingUI::SetLoadingLifeUI()
{
	std::string Index = std::to_string(MarioHelper::MarioLife);
	Index.append(".png");
	LifeUI->SetImage(Index);
}

void LoadingUI::SetLoadingWorldUI()
{
	std::string Index = std::to_string(MarioHelper::MarioWorldCount);
	std::string str;
	for (int i = 0; i < 2; ++i) {
		str = Index.substr(i, 1);
		str.append(".png");
		WorldUIArray[i]->SetImage(str);
	}
}

void LoadingUI::BeginPlay()
{
	for (int i = 0; i < 2; ++i) {
		std::string Index = std::to_string(i);
		WorldUIArray[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		WorldUIArray[i]->SetImage(Index + ".png");
		WorldUIArray[i]->SetTransform(LoadingWorldUITransform);
		LoadingWorldUITransform.AddPosition({ 55,0 });
		WorldUIArray[i]->CameraEffectOff();
	}
	LifeUI = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
	LifeUI->SetImage("1.png");
	LifeUI->SetTransform(LifeUITransform);
	LifeUI->CameraEffectOff();

	CheatUI = CreateImageRenderer(static_cast<int>(MarioRenderOrder::Cheat));
	CheatUI->SetImage("Cheat.png");
	CheatUI->SetTransform(CheatUITransform);
	CheatUI->CameraEffectOff();
}

void LoadingUI::Tick(float _DeltaTime)
{
	SetLoadingLifeUI();
	SetLoadingWorldUI();
}

