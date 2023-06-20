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

#define TAGS "[audio][harmony][compound_interval]"

/*
 - isEnharmonicTo
 - >, <
 - get num semitones
 - hasSameSimpleInterval
*/

TEST_CASE ("CompoundInterval - constructors", TAGS)
{
	using namespace limes::harmony;	 // NOLINT

	using Q = Interval::Quality;

	// Constructors
	{
		auto test_constructors = [] (Q quality, int simpleKind, int octaves)
		{
			const Interval simple { simpleKind, quality };

			const auto compoundKind = (octaves * 7) + simpleKind;

			const CompoundInterval interval1 { compoundKind, quality };
			const CompoundInterval interval2 { octaves, simple };

			REQUIRE (interval1 == interval2);

			REQUIRE (interval1.getNumOctaves() == octaves);
			REQUIRE (interval2.getNumOctaves() == octaves);

			REQUIRE (interval1.getSimpleInterval() == simple);
			REQUIRE (interval2.getSimpleInterval() == simple);

			REQUIRE (interval1.getKind() == compoundKind);
			REQUIRE (interval2.getKind() == compoundKind);
		};

		for (auto octaves = 0; octaves < 5; ++octaves)
		{
			test_constructors (Q::Minor, 2, octaves);
			test_constructors (Q::Major, 2, octaves);
			test_constructors (Q::Diminished, 3, octaves);
			test_constructors (Q::Minor, 3, octaves);
			test_constructors (Q::Major, 3, octaves);
			test_constructors (Q::Augmented, 3, octaves);
			test_constructors (Q::Diminished, 4, octaves);
			test_constructors (Q::Perfect, 4, octaves);
			test_constructors (Q::Augmented, 4, octaves);
			test_constructors (Q::Diminished, 5, octaves);
			test_constructors (Q::Perfect, 5, octaves);
			test_constructors (Q::Augmented, 5, octaves);
			test_constructors (Q::Diminished, 6, octaves);
			test_constructors (Q::Minor, 6, octaves);
			test_constructors (Q::Major, 6, octaves);
			test_constructors (Q::Augmented, 6, octaves);
			test_constructors (Q::Diminished, 7, octaves);
			test_constructors (Q::Minor, 7, octaves);
			test_constructors (Q::Major, 7, octaves);
			test_constructors (Q::Augmented, 7, octaves);
		}
	}

	// Constructor special cases
	{
		const CompoundInterval interval1 {
			1, Interval { 8, Q::Perfect }
		};

		REQUIRE (interval1.getNumOctaves() == 2);

		REQUIRE (interval1.getSimpleInterval() == Interval());

		const CompoundInterval interval2 {
			1, Interval { 8, Q::Augmented }
		};

		REQUIRE (interval2.getNumOctaves() == 2);

		REQUIRE (interval2.getSimpleInterval() == Interval { 0, Q::Augmented });

		const CompoundInterval interval3 {
			1, Interval { 8, Q::Diminished }
		};

		REQUIRE (interval3.getNumOctaves() == 1);

		REQUIRE (interval3.getSimpleInterval() == Interval { 8, Q::Diminished });
	}
}

TEST_CASE ("CompoundInterval - fromPitches()", TAGS)
{
	using namespace limes::harmony;
	namespace i = intervals;

	// perfect fifth
	{
		const auto interval = CompoundInterval::fromPitches (88, 95);

		REQUIRE (interval.getNumOctaves() == 0);
		REQUIRE (interval.getSimpleInterval() == i::perfect::fifth);
		REQUIRE (interval == i::perfect::fifth);
		REQUIRE (interval.getNumSemitones() == 7);
	}

	// perfect octave
	{
		const auto interval = CompoundInterval::fromPitches (57, 69);

		REQUIRE (interval.getNumOctaves() == 1);
		REQUIRE (interval.getSimpleInterval() == i::perfect::unison);
		REQUIRE (interval == i::perfect::octave);
		REQUIRE (interval.getNumSemitones() == 12);
	}

	// major ninth
	{
		const auto interval = CompoundInterval::fromPitches (40, 54);

		REQUIRE (interval.getNumOctaves() == 1);
		REQUIRE (interval.getSimpleInterval() == i::major::second);
		REQUIRE (interval.getNumSemitones() == 14);
	}

	// oct + maj 7th
	{
		const auto interval = CompoundInterval::fromPitches (52, 75);

		REQUIRE (interval.getNumOctaves() == 1);
		REQUIRE (interval.getSimpleInterval() == i::major::seventh);
		REQUIRE (interval.getNumSemitones() == 23);
	}

	// 2 octaves
	{
		const auto interval = CompoundInterval::fromPitches (32, 56);

		REQUIRE (interval.getNumOctaves() == 2);
		REQUIRE (interval.getSimpleInterval() == i::perfect::unison);
		REQUIRE (interval.getNumSemitones() == 24);
	}
}

TEST_CASE ("Comparing CompoundInterval and Interval", TAGS)
{
	using namespace limes::harmony;
	namespace i = intervals;

	// major seventh
	{
		const CompoundInterval compound { 0, i::major::seventh };

		REQUIRE (compound == i::major::seventh);
		REQUIRE (compound < i::perfect::octave);
		REQUIRE (compound > i::major::third);
		REQUIRE (i::major::seventh == compound);
		REQUIRE (i::perfect::octave > compound);
		REQUIRE (i::major::third < compound);
	}

	// octave
	{
		const CompoundInterval compound { 1, i::perfect::unison };

		REQUIRE (compound == i::perfect::octave);
		REQUIRE (compound < i::augmented::octave);
		REQUIRE (compound > i::diminished::fourth);
		REQUIRE (i::perfect::octave == compound);
		REQUIRE (i::augmented::octave > compound);
		REQUIRE (i::diminished::fourth < compound);
	}
}
