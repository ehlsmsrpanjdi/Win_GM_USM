#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class TestLevel : public ULevel
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

private:
};

