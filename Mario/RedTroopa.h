#pragma once
#include "GreenTroopa.h"
#include "GreenTroopa.h"
// ���� :
class RedTroopa : public GreenTroopa
{
public:
	// constrcuter destructer
	RedTroopa();
	~RedTroopa();

	// delete Function
	RedTroopa(const RedTroopa& _Other) = delete;
	RedTroopa(RedTroopa&& _Other) noexcept = delete;
	RedTroopa& operator=(const RedTroopa& _Other) = delete;
	RedTroopa& operator=(RedTroopa&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

