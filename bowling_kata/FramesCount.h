#pragma once
#include <vector>
#include "GameEngine.h"

namespace bowling_kata
{

class FramesCount : public GameEngine
{
public:
	void roll(unsigned pins) final;
	unsigned score() const final;

private:
	bool isStrike(unsigned frameIndex) const;
	unsigned sumOfBallsInFrame(unsigned frameIndex) const;
	unsigned spareBonus(unsigned frameIndex) const;
	unsigned strikeBonus(unsigned frameIndex) const;
	bool isSpare(unsigned frameIndex) const;

private:
	std::vector<unsigned> m_rolls = std::vector<unsigned>(21, 0);
	unsigned m_count = 0;
};

}