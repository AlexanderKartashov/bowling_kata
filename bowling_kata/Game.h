#pragma once
#include <memory>
#include "GameEngine_fwd.h"

namespace bowling_kata
{

class Game
{
public:
	Game(std::shared_ptr<GameEngine> engine);

	unsigned score() const;
	void roll(unsigned pins);

private:
	std::shared_ptr<GameEngine> m_engine;
};

}