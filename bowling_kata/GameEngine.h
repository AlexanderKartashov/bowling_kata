#pragma once

namespace bowling_kata
{

class GameEngine
{
public:
	virtual ~GameEngine() = default;

	virtual void roll(unsigned pins) = 0;
	virtual unsigned score() const = 0;
};

}