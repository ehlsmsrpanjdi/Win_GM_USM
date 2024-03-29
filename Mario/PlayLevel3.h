#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform/EngineSound.h>

// ���� :
class PlayLevel3 : public ULevel
{
public:
	// constrcuter destructer
	PlayLevel3();
	~PlayLevel3();

	// delete Function
	PlayLevel3(const PlayLevel3& _Other) = delete;
	PlayLevel3(PlayLevel3&& _Other) noexcept = delete;
	PlayLevel3& operator=(const PlayLevel3& _Other) = delete;
	PlayLevel3& operator=(PlayLevel3&& _Other) noexcept = delete;

protected:
	UEngineSoundPlayer BGMPlayer;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* Level) override;
	void LevelEnd(ULevel* Level) override;
private:

};

