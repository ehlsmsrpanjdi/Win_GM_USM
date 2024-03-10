#pragma once
#include "LeftPipe.h"
// Ό³Έν :
class Stage2Pipe : public LeftPipe
{
public:
	// constrcuter destructer
	Stage2Pipe();
	~Stage2Pipe();

	// delete Function
	Stage2Pipe(const Stage2Pipe& _Other) = delete;
	Stage2Pipe(Stage2Pipe&& _Other) noexcept = delete;
	Stage2Pipe& operator=(const Stage2Pipe& _Other) = delete;
	Stage2Pipe& operator=(Stage2Pipe&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	UCollision* TeleportCollision;
private:

};

