#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class GameOverLogo : public AActor
{
public:
	// constrcuter destructer
	GameOverLogo();
	~GameOverLogo();

	// delete Function
	GameOverLogo(const GameOverLogo& _Other) = delete;
	GameOverLogo(GameOverLogo&& _Other) noexcept = delete;
	GameOverLogo& operator=(const GameOverLogo& _Other) = delete;
	GameOverLogo& operator=(GameOverLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

