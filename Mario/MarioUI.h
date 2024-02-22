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

	void SetMarioScore();
	void SetMarioTime(float _DeltaTime);

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	float Time = 0;

private:
	UImageRenderer* PlayerUIRenderer = nullptr;

	int MarioScoreIndex = 6;
	UImageRenderer* ScoreUIArray[6] = { nullptr, };
	UImageRenderer* TimeUIArray[3] = { nullptr, };

};

