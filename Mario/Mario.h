#pragma once
#include <EngineCore\Actor.h>

// ���� :
class Mario : public AActor
{
public:
	// constrcuter destructer
	Mario();
	~Mario();

	// delete Function
	Mario(const Mario& _Other) = delete;
	Mario(Mario&& _Other) noexcept = delete;
	Mario& operator=(const Mario& _Other) = delete;
	Mario& operator=(Mario&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

