#include "stdafx.h"
#include "RollsList.h"
#include "Constants.h"
#include <boost/range/irange.hpp>
#include <algorithm>
#include <numeric>
#include <execution>

namespace bowling_kata
{

void RollsList::roll(unsigned pins)
{
	m_rolls[m_count++] = pins;
}

unsigned RollsList::score() const
{
	unsigned score = 0;
	unsigned frame = 1;
	bool newFrame = true;
	unsigned addBonus = 0;
	for (unsigned i = 0; i < m_rolls.size(); ++i)
	{
		const bool notLastFrame = frame != 10;
		auto const roll = m_rolls[i];

		if (addBonus)
		{
			score += roll;
			--addBonus;
		}

		if (newFrame)
		{
			if (roll == MAX_PINS)
			{
				if (frame != 10)
				{
					newFrame = true;
					++frame;
				}
				if (addBonus && (frame != 10))
				{
					score += roll;
				}
				addBonus = 2;
			}
			else
			{
				newFrame = false;
			}
		}
		else
		{
			if (((roll + m_rolls[i - 1]) == MAX_PINS) && (frame != 10))
			{
				addBonus = 1;
			}

			if (frame != 10)
			{
				newFrame = true;
				++frame;
			}
		}

		score += roll;
	}
	return score;
}

}