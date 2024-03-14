#pragma once
#include <EngineCore/Level.h>
// Ό³Έν :
class GameOverLevel : public ULevel
{
public:
	// constrcuter destructer
	GameOverLevel();
	~GameOverLevel();

	// delete Function
	GameOverLevel(const GameOverLevel& _Other) = delete;
	GameOverLevel(GameOverLevel&& _Other) noexcept = delete;
	GameOverLevel& operator=(const GameOverLevel& _Other) = delete;
	GameOverLevel& operator=(GameOverLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;
	void Tick(float _DeltaTime) override;
	float RestartTime = 5.0f;
private:

};

