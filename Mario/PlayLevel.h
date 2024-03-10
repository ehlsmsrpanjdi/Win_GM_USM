#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform\EngineSound.h>

// Ό³Έν :
class UPlayLevel : public ULevel
{
public:
	// constrcuter destructer
	UPlayLevel();
	~UPlayLevel();

	// delete Function
	UPlayLevel(const UPlayLevel& _Other) = delete;
	UPlayLevel(UPlayLevel&& _Other) noexcept = delete;
	UPlayLevel& operator=(const UPlayLevel& _Other) = delete;
	UPlayLevel& operator=(UPlayLevel&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* Level) override;
	UEngineSoundPlayer BGMPlayer;
private:

};

