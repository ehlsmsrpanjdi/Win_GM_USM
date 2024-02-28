#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class MarioUI : public AActor
{
public:
	// constrcuter destructer
	MarioUI();
	~MarioUI();

	// delete Function
	MarioUI(const MarioUI& _Other) = delete;
	MarioUI(MarioUI&& _Other) noexcept = delete;
	MarioUI& operator=(const MarioUI& _Other) = delete;
	MarioUI& operator=(MarioUI&& _Other) noexcept = delete;

	void SetMarioScoreUI();
	void SetMarioTimeUI(float _DeltaTime);
	void SetMarioCoinUI();
	void SetMarioWorldUI();

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	float Time = 0;

	FTransform MainUITransform = { { 296,-136 }, { 1024, 108 } };
	FTransform ScoreUITransform = { {-110 ,-95}, {20,20} };
	FTransform CoinUITransform = { { 165 ,-95}, {128,128} };
	FTransform CoinCountUITransform = { { 230 ,-95}, {20,20} };
	FTransform WorldUITransform = { {430 ,-95}, {20,20} };
	FTransform TimeUITransform { {640 , -95}, {20,20} };
	int PlusSize = 35;

	void IsLevelEnd(float _DeltaTime);
	float ChangeLevelTime = 5.0f;
	float MinusTime = 0.004f;

private:
	UImageRenderer* PlayerUIRenderer = nullptr;

	int MarioScoreIndex = 6;
	UImageRenderer* ScoreUIArray[6] = { nullptr, };
	UImageRenderer* CoinUIArray[2] = { nullptr, };
	UImageRenderer* WorldUIArray[2] = { nullptr, };
	UImageRenderer* TimeUIArray[3] = { nullptr, };
	UImageRenderer* CoinImage = nullptr;

};

