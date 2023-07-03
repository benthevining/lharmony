/*
 * ======================================================================================
 *  __    ____  __  __  ____  ___
 * (  )  (_  _)(  \/  )( ___)/ __)
 *  )(__  _)(_  )    (  )__) \__ \
 * (____)(____)(_/\/\_)(____)(___/
 *
 *  This file is part of the Limes open source library and is licensed under the terms of the GNU Public License.
 *
 *  Commercial licenses are available; contact the maintainers at ben.the.vining@gmail.com to inquire for details.
 *
 * ======================================================================================
 */

#include "lharmony/lharmony.h"
#include <catch2/catch_test_macros.hpp>

namespace h = limes::harmony;

#define TAGS "[audio][harmony][OvertoneSeries]"

const h::OvertoneSeries series { h::Pitch::fromFreq (110) };

TEST_CASE ("OvertoneSeries - getHarmonic()", TAGS)
{
	REQUIRE (series.getHarmonic (0UL) == series.getFundamental());
	REQUIRE (series.getHarmonic (1UL) == h::Pitch::fromFreq (220));
	REQUIRE (series.getHarmonic (2UL) == h::Pitch::fromFreq (330));
	REQUIRE (series[3UL] == h::Pitch::fromFreq (440));
	REQUIRE (series[4UL] == h::Pitch::fromFreq (550));
	REQUIRE (series[5UL] == h::Pitch::fromFreq (660));
}

TEST_CASE ("OvertoneSeries - getIntervalOfHarmonic()", TAGS)
{
	namespace i = h::intervals;

	REQUIRE (series.getIntervalOfHarmonic (0UL) == i::perfect::unison);
	REQUIRE (series.getIntervalOfHarmonic (1UL) == i::perfect::octave);
	REQUIRE (series.getIntervalOfHarmonic (2UL) == h::CompoundInterval { 1, i::perfect::fifth });
	REQUIRE (series.getIntervalOfHarmonic (3UL) == h::CompoundInterval { 2, i::perfect::unison });
	REQUIRE (series.getIntervalOfHarmonic (4UL) == h::CompoundInterval { 2, i::major::third });
	REQUIRE (series.getIntervalOfHarmonic (5UL) == h::CompoundInterval { 2, i::perfect::fifth });
}
