#pragma once
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineSound.h>
// Ό³Έν :
class LastLevel : public ULevel
{
public:
	// constrcuter destructer
	LastLevel();
	~LastLevel();

	// delete Function
	LastLevel(const LastLevel& _Other) = delete;
	LastLevel(LastLevel&& _Other) noexcept = delete;
	LastLevel& operator=(const LastLevel& _Other) = delete;
	LastLevel& operator=(LastLevel&& _Other) noexcept = delete;

protected:
	UEngineSoundPlayer BGMPlayer;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* Level) override;
	void LevelEnd(ULevel* Level) override;
private:

};

