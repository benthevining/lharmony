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
#include <vector>
#include <catch2/catch_test_macros.hpp>

// getIntervals()
// containsPitch()
// getPitchClasses()
// getPitches()

#define TAGS "[audio][harmony][scales][KeySignature]"

using namespace limes::harmony;	 // NOLINT
using KeySignature = scales::KeySignature;
namespace k		   = scales::keys;

static const std::vector<int> majorScaleIntervals { 2, 2, 1, 2, 2, 2, 1 };
static const std::vector<int> naturalMinorIntervals { 2, 1, 2, 2, 1, 2, 2 };
static const std::vector<int> harmonicMinorIntervals { 2, 1, 2, 2, 1, 3, 1 };

TEST_CASE ("KeySignature - relative", TAGS)
{
	auto test_relative_pair = [] (const KeySignature& majorKey, const KeySignature& minorKey)
	{
		REQUIRE (majorKey.isRelativeKeyOf (minorKey));
		REQUIRE (minorKey.isRelativeKeyOf (majorKey));
		REQUIRE (majorKey.getRelativeKey() == minorKey);
		REQUIRE (minorKey.getRelativeKey() == majorKey);

		REQUIRE (majorKey.isMajorKey());
		REQUIRE (minorKey.isMinorKey());

		REQUIRE (majorKey.getIntervalsAsSemitones() == majorScaleIntervals);
		REQUIRE (minorKey.getIntervalsAsSemitones() == naturalMinorIntervals);
		REQUIRE (minorKey.withType (KeySignature::Type::HarmonicMinor).getIntervalsAsSemitones() == harmonicMinorIntervals);

		const auto interval = Interval::fromPitches (majorKey.getRoot (3), minorKey.getRoot (3));

		REQUIRE ((interval == intervals::minor::third || interval.getInverse() == intervals::minor::third));
	};

	test_relative_pair (k::major::c, k::minor::a);
	test_relative_pair (k::major::cSharp, k::minor::aSharp);
	test_relative_pair (k::major::cFlat, k::minor::aFlat);
	test_relative_pair (k::major::d, k::minor::b);
	test_relative_pair (k::major::dFlat, k::minor::bFlat);
	test_relative_pair (k::major::e, k::minor::cSharp);
	test_relative_pair (k::major::eFlat, k::minor::c);
	test_relative_pair (k::major::f, k::minor::d);
	test_relative_pair (k::major::fSharp, k::minor::dSharp);
	test_relative_pair (k::major::g, k::minor::e);
	test_relative_pair (k::major::gFlat, k::minor::eFlat);
	test_relative_pair (k::major::a, k::minor::fSharp);
	test_relative_pair (k::major::aFlat, k::minor::f);
	test_relative_pair (k::major::b, k::minor::gSharp);
	test_relative_pair (k::major::bFlat, k::minor::g);
}

TEST_CASE ("KeySignature - parallel", TAGS)
{
	auto test_parallel_pair = [] (const KeySignature& majorKey, const KeySignature& minorKey)
	{
		REQUIRE (majorKey.isParallelKeyOf (minorKey));
		REQUIRE (minorKey.isParallelKeyOf (majorKey));
		REQUIRE (majorKey.getParallelKey() == minorKey);
		REQUIRE (minorKey.getParallelKey() == majorKey);

		REQUIRE (majorKey.isMajorKey());
		REQUIRE (minorKey.isMinorKey());

		REQUIRE (majorKey.getIntervalsAsSemitones() == majorScaleIntervals);
		REQUIRE (minorKey.getIntervalsAsSemitones() == naturalMinorIntervals);
		REQUIRE (minorKey.withType (KeySignature::Type::HarmonicMinor).getIntervalsAsSemitones() == harmonicMinorIntervals);

		REQUIRE (majorKey.getPitchClassOfRoot() == minorKey.getPitchClassOfRoot());
	};

	test_parallel_pair (k::major::c, k::minor::c);
	test_parallel_pair (k::major::cSharp, k::minor::cSharp);
	test_parallel_pair (k::major::d, k::minor::d);
	test_parallel_pair (k::major::e, k::minor::e);
	test_parallel_pair (k::major::eFlat, k::minor::eFlat);
	test_parallel_pair (k::major::f, k::minor::f);
	test_parallel_pair (k::major::fSharp, k::minor::fSharp);
	test_parallel_pair (k::major::g, k::minor::g);
	test_parallel_pair (k::major::a, k::minor::a);
	test_parallel_pair (k::major::aFlat, k::minor::aFlat);
	test_parallel_pair (k::major::b, k::minor::b);
	test_parallel_pair (k::major::bFlat, k::minor::bFlat);
}

TEST_CASE ("KeySignature - enharmonic", TAGS)
{
	auto test_enharmonic_pair = [] (const KeySignature& key1, const KeySignature& key2)
	{
		REQUIRE (key1.hasEnharmonicKey());
		REQUIRE (key2.hasEnharmonicKey());
		REQUIRE (key1.isEnharmonicKeyOf (key2));
		REQUIRE (key2.isEnharmonicKeyOf (key1));
		REQUIRE (key1.getEnharmonicKey() == key2);
		REQUIRE (key2.getEnharmonicKey() == key1);
		REQUIRE (key1.getPitchClassOfRoot() == key2.getPitchClassOfRoot());
	};

	test_enharmonic_pair (k::major::cSharp, k::major::dFlat);
	test_enharmonic_pair (k::major::cFlat, k::major::b);
	test_enharmonic_pair (k::major::dFlat, k::major::cSharp);
	test_enharmonic_pair (k::minor::dSharp, k::minor::eFlat);
	test_enharmonic_pair (k::major::fSharp, k::major::gFlat);
	test_enharmonic_pair (k::minor::gSharp, k::minor::aFlat);
	test_enharmonic_pair (k::minor::aSharp, k::minor::bFlat);
}

TEST_CASE ("KeySignature", TAGS)
{
	{
		const auto cMajor = KeySignature { KeySignature::Type::Major, PitchClass { 0 } };

		REQUIRE (! cMajor.hasEnharmonicKey());
		REQUIRE (! cMajor.isFlatKey());
		REQUIRE (! cMajor.isSharpKey());

		REQUIRE (cMajor.isMajorKey());

		REQUIRE (cMajor.getPitchClassOfRoot().isWhiteKey());

		REQUIRE (cMajor.getNumSharps() == 0);
		REQUIRE (cMajor.getNumFlats() == 0);

		REQUIRE (cMajor.getIntervalsAsSemitones() == majorScaleIntervals);

		REQUIRE (cMajor.getPitchClassOfScaleDegree (0) == 0);
		REQUIRE (cMajor.getPitchClassOfScaleDegree (1) == 0);
		REQUIRE (cMajor.getPitchClassOfScaleDegree (6) == 9);
		REQUIRE (cMajor.getPitchClassOfScaleDegree (8) == 0);

		REQUIRE (cMajor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (! cMajor.containsPitchClass (PitchClass { 1 }));
		REQUIRE (cMajor.containsPitchClass (PitchClass { 5 }));
		REQUIRE (! cMajor.containsPitchClass (PitchClass { 6 }));

		const auto aMinor = cMajor.getRelativeKey();

		REQUIRE (aMinor.isMinorKey());
		REQUIRE (aMinor.getNumFlats() == 0);
		REQUIRE (aMinor.getNumSharps() == 0);
		REQUIRE (aMinor.getPitchClassOfRoot().getAsInt() == 9);

		REQUIRE (aMinor.getIntervalsAsSemitones() == naturalMinorIntervals);

		REQUIRE (aMinor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (! aMinor.containsPitchClass (PitchClass { 1 }));
		REQUIRE (aMinor.containsPitchClass (PitchClass { 5 }));
		REQUIRE (! aMinor.containsPitchClass (PitchClass { 6 }));

		const auto aMajor = aMinor.getParallelKey();

		{
			const auto aHarmMinor = aMinor.withType (KeySignature::Type::HarmonicMinor);

			REQUIRE (aHarmMinor.isMinorKey());
			REQUIRE (aHarmMinor.getNumFlats() == 0);
			REQUIRE (aHarmMinor.getNumSharps() == 0);
			REQUIRE (aHarmMinor.getIntervalsAsSemitones() == harmonicMinorIntervals);
			REQUIRE (aHarmMinor.getPitchClassOfRoot() == 9);
			REQUIRE (aHarmMinor.containsPitchClass (PitchClass { 8 }));
			REQUIRE (! aHarmMinor.containsPitchClass (PitchClass { 7 }));
		}

		REQUIRE (aMinor.getPitchClassOfScaleDegree (4) == 2);
		REQUIRE (aMinor.getPitchClassOfScaleDegree (7) == 7);

		REQUIRE (aMajor.isSharpKey());
		REQUIRE (aMajor.isMajorKey());
		REQUIRE (aMajor.getNumSharps() == 3);
		REQUIRE (aMajor.getPitchClassOfRoot() == aMinor.getPitchClassOfRoot());

		REQUIRE (aMajor.getIntervalsAsSemitones() == majorScaleIntervals);

		REQUIRE (! aMajor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (aMajor.containsPitchClass (PitchClass { 1 }));
		REQUIRE (aMajor.containsPitchClass (PitchClass { 11 }));
		REQUIRE (! aMajor.containsPitchClass (PitchClass { 10 }));

		const auto FSharpMinor = aMajor.getRelativeKey();

		REQUIRE (FSharpMinor.isSharpKey());
		REQUIRE (FSharpMinor.isMinorKey());
		REQUIRE (FSharpMinor.getNumSharps() == 3);
		REQUIRE (FSharpMinor.getPitchClassOfRoot() == 6);

		REQUIRE (FSharpMinor.getIntervalsAsSemitones() == naturalMinorIntervals);

		REQUIRE (! FSharpMinor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (FSharpMinor.containsPitchClass (PitchClass { 1 }));
		REQUIRE (FSharpMinor.containsPitchClass (PitchClass { 11 }));
		REQUIRE (! FSharpMinor.containsPitchClass (PitchClass { 10 }));

		REQUIRE (FSharpMinor.withType (KeySignature::Type::HarmonicMinor).getIntervalsAsSemitones() == harmonicMinorIntervals);

		const auto cMinor = cMajor.getParallelKey();

		REQUIRE (cMinor.isMinorKey());
		REQUIRE (cMinor.isFlatKey());
		REQUIRE (cMinor.getNumFlats() == 3);
		REQUIRE (cMinor.getPitchClassOfRoot() == cMajor.getPitchClassOfRoot());

		REQUIRE (cMinor.getIntervalsAsSemitones() == naturalMinorIntervals);

		REQUIRE (! cMinor.containsPitchClass (PitchClass { 4 }));
		REQUIRE (cMinor.containsPitchClass (PitchClass { 3 }));
		REQUIRE (cMinor.containsPitchClass (PitchClass { 7 }));
		REQUIRE (cMinor.containsPitchClass (PitchClass { 8 }));

		REQUIRE (cMinor.withType (KeySignature::Type::HarmonicMinor).getIntervalsAsSemitones() == harmonicMinorIntervals);

		const auto EFlatMajor = cMinor.getRelativeKey();

		REQUIRE (EFlatMajor.isMajorKey());
		REQUIRE (EFlatMajor.isFlatKey());
		REQUIRE (EFlatMajor.getNumFlats() == 3);
		REQUIRE (EFlatMajor.getPitchClassOfRoot() == 3);

		REQUIRE (! EFlatMajor.containsPitchClass (PitchClass { 4 }));
		REQUIRE (EFlatMajor.containsPitchClass (PitchClass { 3 }));
		REQUIRE (EFlatMajor.containsPitchClass (PitchClass { 7 }));
		REQUIRE (EFlatMajor.containsPitchClass (PitchClass { 8 }));

		REQUIRE (EFlatMajor.getIntervalsAsSemitones() == majorScaleIntervals);
	}

	{
		const KeySignature FSharpMajor { KeySignature::Type::Major, true, PitchClass { 6 } };

		REQUIRE (FSharpMajor.isMajorKey());
		REQUIRE (FSharpMajor.isSharpKey());
		REQUIRE (FSharpMajor.getNumSharps() == 6);

		REQUIRE (! FSharpMajor.containsPitchClass (PitchClass { 4 }));
		REQUIRE (FSharpMajor.containsPitchClass (PitchClass { 3 }));
		REQUIRE (! FSharpMajor.containsPitchClass (PitchClass { 7 }));
		REQUIRE (FSharpMajor.containsPitchClass (PitchClass { 6 }));

		const auto GFlatMajor = FSharpMajor.getEnharmonicKey();

		REQUIRE (GFlatMajor.isMajorKey());
		REQUIRE (GFlatMajor.isFlatKey());
		REQUIRE (GFlatMajor.getNumFlats() == 6);

		REQUIRE (GFlatMajor.getPitchClassOfRoot() == FSharpMajor.getPitchClassOfRoot());

		REQUIRE (! GFlatMajor.containsPitchClass (PitchClass { 4 }));
		REQUIRE (GFlatMajor.containsPitchClass (PitchClass { 3 }));
		REQUIRE (! GFlatMajor.containsPitchClass (PitchClass { 7 }));
		REQUIRE (GFlatMajor.containsPitchClass (PitchClass { 6 }));
	}

	{
		const KeySignature cFlatMajor { 7, false, KeySignature::Type::Major };

		REQUIRE (cFlatMajor.isMajorKey());
		REQUIRE (cFlatMajor.isFlatKey());
		REQUIRE (cFlatMajor.getNumFlats() == 7);
		REQUIRE (cFlatMajor.getNumSharps() == 0);
		REQUIRE (cFlatMajor.getPitchClassOfRoot() == 11);

		REQUIRE (! cFlatMajor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (cFlatMajor.containsPitchClass (PitchClass { 11 }));
		REQUIRE (! cFlatMajor.containsPitchClass (PitchClass { 9 }));
		REQUIRE (cFlatMajor.containsPitchClass (PitchClass { 10 }));

		const auto bMajor = cFlatMajor.getEnharmonicKey();

		REQUIRE (bMajor.isMajorKey());
		REQUIRE (bMajor.isSharpKey());
		REQUIRE (bMajor.getNumSharps() == 5);
		REQUIRE (bMajor.getPitchClassOfRoot() == 11);

		REQUIRE (! bMajor.containsPitchClass (PitchClass { 0 }));
		REQUIRE (bMajor.containsPitchClass (PitchClass { 11 }));
		REQUIRE (! bMajor.containsPitchClass (PitchClass { 9 }));
		REQUIRE (bMajor.containsPitchClass (PitchClass { 10 }));
	}
}

#undef TAGS
