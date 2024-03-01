#pragma once

// Ό³Έν :
class Hammer
{
public:
	// constrcuter destructer
	Hammer();
	~Hammer();

	// delete Function
	Hammer(const Hammer& _Other) = delete;
	Hammer(Hammer&& _Other) noexcept = delete;
	Hammer& operator=(const Hammer& _Other) = delete;
	Hammer& operator=(Hammer&& _Other) noexcept = delete;

protected:

private:

};

