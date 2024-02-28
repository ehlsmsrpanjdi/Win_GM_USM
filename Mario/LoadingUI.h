#pragma once
#include "MarioUI.h"
#include <EngineCore/Actor.h>
// Ό³Έν :
class LoadingUI : public AActor
{
public:
	// constrcuter destructer
	LoadingUI();
	~LoadingUI();

	// delete Function
	LoadingUI(const LoadingUI& _Other) = delete;
	LoadingUI(LoadingUI&& _Other) noexcept = delete;
	LoadingUI& operator=(const LoadingUI& _Other) = delete;
	LoadingUI& operator=(LoadingUI&& _Other) noexcept = delete;

	void SetLoadingLifeUI();
	void SetLoadingWorldUI();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	FTransform LoadingWorldUITransform = { {365 ,138}, {20,20} };
	FTransform LifeUITransform= { { 390,262}, {20,20} };

	UImageRenderer* WorldUIArray[2] = { nullptr, };
	UImageRenderer* LifeUI = nullptr;
};

