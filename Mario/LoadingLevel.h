#pragma once
#include <EngineCore/Level.h>
#include <EngineCore/ImageRenderer.h>

// Ό³Έν :
class LoadingLevel : public ULevel
{
public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	UImageRenderer* LoadingImage = nullptr;

	void LevelStart(ULevel* Level) override;
	void LevelEnd(ULevel* Level) override;
	

protected:

	UImageRenderer* WorldUIArray[2] = { nullptr, };
	UImageRenderer* MarioLifeUI = nullptr;
	float LevelChangeTime = 3.f;

private:

};

