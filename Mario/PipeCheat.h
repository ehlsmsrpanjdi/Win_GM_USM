#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class PipeCheat : public AActor
{
public:
	// constrcuter destructer
	PipeCheat();
	~PipeCheat();

	// delete Function
	PipeCheat(const PipeCheat& _Other) = delete;
	PipeCheat(PipeCheat&& _Other) noexcept = delete;
	PipeCheat& operator=(const PipeCheat& _Other) = delete;
	PipeCheat& operator=(PipeCheat&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	UImageRenderer* BodyRenderer = nullptr;
private:

};

