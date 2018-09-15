#include "stdafx.h"
#include "../bowling_kata/Game.h"
#include "../bowling_kata/RollsList.h"
#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <functional>
#include <boost/range/algorithm/for_each.hpp>

using namespace bowling_kata;
using namespace std;

using Rolls = vector<unsigned>;
using DataSet = pair<Rolls, unsigned>;
using GameEngineCreator = function<shared_ptr<GameEngine>()>;

namespace
{

static const vector<DataSet> testData{
	DataSet{ Rolls{}, 0u },
	DataSet{ Rolls{ 2u }, 2u },
	DataSet{ Rolls{ 3u, 2u, 4u }, 9u },
	DataSet{ Rolls{ 8u, 2u, 4u }, 18u }, // spare
	DataSet{ Rolls{ 5u, 6u, 4u, 2u, 2u }, 19u }, // non spare
	DataSet{ Rolls{ 10u, 3u, 4u }, 24u }, // strike
	DataSet{ Rolls{ 0u, 10u, 4u, 5u }, 23u }, // non srike
	DataSet{ Rolls(12, 10u), 300u }, // all strikes
	DataSet{ Rolls(21, 5u), 150u }, // all spares
	DataSet{ Rolls(20, 1u), 20u }, // all ones
	DataSet{ Rolls{9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u, 9u, 0u}, 90u } // all non spares
};

}

struct GameTest : public ::testing::TestWithParam<std::tuple<DataSet, GameEngineCreator>>
{
protected:
	virtual void SetUp()
	{
		game = make_shared<Game>(::testing::get<1>(GetParam())());
	}

	virtual void TearDown()
	{
		game = nullptr;
	}

	std::shared_ptr<Game> game; 
};

TEST_P(GameTest, RollsTest)
{
	auto const& dataSet = ::testing::get<0>(GetParam());
	boost::for_each(dataSet.first, [&](const auto& roll) { this->game->roll(roll); });
	ASSERT_THAT(this->game->score(), ::testing::Eq(dataSet.second));
}

INSTANTIATE_TEST_CASE_P(AllCombinationsTests,
	GameTest,
	::testing::Combine(
		::testing::ValuesIn(testData),
		::testing::Values([] {return make_shared<RollsList>(); })
	)
);