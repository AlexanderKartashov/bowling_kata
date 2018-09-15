#include "stdafx.h"
#include "Game.h"
#include "GameEngine.h"

namespace bowling_kata
{

Game::Game(std::shared_ptr<GameEngine> engine)
{
	m_engine = engine;
}

unsigned Game::score() const
{
	return m_engine->score();
}

void Game::roll(unsigned pins)
{
	m_engine->roll(pins);
}

}