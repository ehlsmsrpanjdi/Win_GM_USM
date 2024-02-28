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
	

protected:

private:

};

