#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class PlayLevel2 : public ULevel
{
public:
	// constrcuter destructer
	PlayLevel2();
	~PlayLevel2();

	// delete Function
	PlayLevel2(const PlayLevel2& _Other) = delete;
	PlayLevel2(PlayLevel2&& _Other) noexcept = delete;
	PlayLevel2& operator=(const PlayLevel2& _Other) = delete;
	PlayLevel2& operator=(PlayLevel2&& _Other) noexcept = delete;

protected:
	UEngineSoundPlayer BGMPlayer;
	float Level2SoundTime = 6;
	bool Level2SoundStart = false;
	bool Level2SoundEnd = false;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* Level) override;
private:

};

