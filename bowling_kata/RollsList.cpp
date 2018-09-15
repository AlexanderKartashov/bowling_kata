#include "stdafx.h"
#include "RollsList.h"
#include "Constants.h"
#include <boost/range/irange.hpp>
#include <algorithm>
#include <numeric>
#include <execution>

namespace bowling_kata
{

bool RollsList::isStrike(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) == MAX_PINS;
}

unsigned RollsList::sumOfBallsInFrame(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) + m_rolls.at(frameIndex + 1);
}

unsigned RollsList::spareBonus(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex + 2);
}

unsigned RollsList::strikeBonus(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex + 1) + m_rolls.at(frameIndex + 2);
}

bool RollsList::isSpare(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) + m_rolls.at(frameIndex + 1) == MAX_PINS;
}

void RollsList::roll(unsigned pins)
{
	m_rolls[m_count++] = pins;
}

unsigned RollsList::score() const
{
	unsigned frameIndex = 0;
	auto const reduction = [&](unsigned total, unsigned) {
		unsigned result = 0;
		if (isStrike(frameIndex))
		{
			result = MAX_PINS + strikeBonus(frameIndex);
			frameIndex++;
		}
		else if (isSpare(frameIndex))
		{
			result = MAX_PINS + spareBonus(frameIndex);
			frameIndex += 2;
		}
		else
		{
			result = sumOfBallsInFrame(frameIndex);
			frameIndex += 2;
		}
		return result + total;
	};
	auto const indices = boost::irange(0u, 10u);
	return std::reduce(std::execution::sequenced_policy{}, indices.begin(), indices.end(), 0, reduction);
}

}