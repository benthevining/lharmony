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
#include <catch2/catch_all.hpp>

#define TAGS "[audio][harmony][utils]"

namespace harmony = limes::harmony;

TEST_CASE ("Freq/MIDI conversion", TAGS)
{
	static constexpr auto MARGIN = 0.01;

	{
		static constexpr auto freq = 8.18;
		static constexpr auto midi = 0;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 27.5;
		static constexpr auto midi = 21;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 98.;
		static constexpr auto midi = 43;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 349.23;
		static constexpr auto midi = 65;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 1046.5;
		static constexpr auto midi = 84;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 3520.;
		static constexpr auto midi = 105;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}

	{
		static constexpr auto freq = 12543.85;
		static constexpr auto midi = 127;

		REQUIRE_THAT (harmony::midiToFreq (midi),
					  Catch::Matchers::WithinAbs (freq, MARGIN));

		REQUIRE_THAT (harmony::freqToMidi (freq),
					  Catch::Matchers::WithinAbs (midi, MARGIN));
	}
}

#undef TAGS
