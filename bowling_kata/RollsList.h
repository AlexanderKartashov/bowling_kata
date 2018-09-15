#pragma once
#include <vector>
#include "GameEngine.h"

namespace bowling_kata
{

class RollsList : public GameEngine
{
public:
	void roll(unsigned pins) final;
	unsigned score() const final;

private:
	std::vector<unsigned> m_rolls = std::vector<unsigned>(21, 0);
	unsigned m_count = 0;
};

}