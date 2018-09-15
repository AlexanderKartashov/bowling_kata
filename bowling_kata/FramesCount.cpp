#include "stdafx.h"
#include "FramesCount.h"
#include "Constants.h"
#include <boost/range/irange.hpp>
#include <algorithm>
#include <numeric>
#include <execution>

namespace bowling_kata
{

bool FramesCount::isStrike(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) == MAX_PINS;
}

unsigned FramesCount::sumOfBallsInFrame(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) + m_rolls.at(frameIndex + 1);
}

unsigned FramesCount::spareBonus(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex + 2);
}

unsigned FramesCount::strikeBonus(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex + 1) + m_rolls.at(frameIndex + 2);
}

bool FramesCount::isSpare(unsigned frameIndex) const
{
	return m_rolls.at(frameIndex) + m_rolls.at(frameIndex + 1) == MAX_PINS;
}

void FramesCount::roll(unsigned pins)
{
	m_rolls[m_count++] = pins;
}

unsigned FramesCount::score() const
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