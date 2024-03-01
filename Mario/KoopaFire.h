#pragma once

// Ό³Έν :
class KoopaFire
{
public:
	// constrcuter destructer
	KoopaFire();
	~KoopaFire();

	// delete Function
	KoopaFire(const KoopaFire& _Other) = delete;
	KoopaFire(KoopaFire&& _Other) noexcept = delete;
	KoopaFire& operator=(const KoopaFire& _Other) = delete;
	KoopaFire& operator=(KoopaFire&& _Other) noexcept = delete;

protected:

private:

};

