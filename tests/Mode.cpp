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

#define TAGS "[audio][harmony][scales][mode]"

// getIntervalsAsSemitones()
// getIntervals()
// containsPitch()
// getPitchClasses()
// getPitches()
// getPitchClassOfScaleDegree()

using namespace limes::harmony;	 // NOLINT
using scales::Mode;

TEST_CASE ("Mode - Ionian", TAGS)
{
	const Mode cIonian { Mode::Type::Ionian, PitchClass { 0 } };

	REQUIRE (cIonian.getNumFlats() == 0);
	REQUIRE (cIonian.getNumSharps() == 0);

	const auto cMajor = cIonian.getKeySignature();

	REQUIRE (cMajor.isMajorKey());
	REQUIRE (cMajor.getNumFlats() == 0);
	REQUIRE (cMajor.getNumSharps() == 0);
	REQUIRE (cMajor.getPitchClassOfRoot() == 0);

	const Mode bFlatIonian { Mode::Type::Ionian, PitchClass { 10 } };

	REQUIRE (bFlatIonian.getNumFlats() == 2);
	REQUIRE (bFlatIonian.getNumSharps() == 0);

	const auto bFlatMajor = bFlatIonian.getKeySignature();

	REQUIRE (bFlatMajor.isMajorKey());
	REQUIRE (bFlatMajor.getNumFlats() == 2);
	REQUIRE (bFlatMajor.getNumSharps() == 0);
	REQUIRE (bFlatMajor.getPitchClassOfRoot() == 10);
}

TEST_CASE ("Mode - Dorian", TAGS)
{
	const Mode dDorian { Mode::Type::Dorian, PitchClass { 2 } };

	REQUIRE (dDorian.getNumFlats() == 0);
	REQUIRE (dDorian.getNumSharps() == 0);

	const auto cMajor = dDorian.getKeySignature();

	REQUIRE (cMajor.isMajorKey());
	REQUIRE (cMajor.getNumFlats() == 0);
	REQUIRE (cMajor.getNumSharps() == 0);
	REQUIRE (cMajor.getPitchClassOfRoot() == 0);

	const Mode gDorian { Mode::Type::Dorian, PitchClass { 7 } };

	REQUIRE (gDorian.getNumFlats() == 1);
	REQUIRE (gDorian.getNumSharps() == 0);

	const auto fMajor = gDorian.getKeySignature();

	REQUIRE (fMajor.isMajorKey());
	REQUIRE (fMajor.getNumFlats() == 1);
	REQUIRE (fMajor.getNumSharps() == 0);
	REQUIRE (fMajor.getPitchClassOfRoot() == 5);

	const Mode bDorian { Mode::Type::Dorian, PitchClass { 11 } };

	REQUIRE (bDorian.getNumFlats() == 0);
	REQUIRE (bDorian.getNumSharps() == 3);

	const auto aMajor = bDorian.getKeySignature();

	REQUIRE (aMajor.isMajorKey());
	REQUIRE (aMajor.getNumFlats() == 0);
	REQUIRE (aMajor.getNumSharps() == 3);
	REQUIRE (aMajor.getPitchClassOfRoot() == 9);
}

TEST_CASE ("Mode - Phrygian", TAGS)
{
	const Mode fPhrygian { Mode::Type::Phrygian, PitchClass { 5 } };

	REQUIRE (fPhrygian.getNumFlats() == 5);
	REQUIRE (fPhrygian.getNumSharps() == 0);

	const auto dFlatMajor = fPhrygian.getKeySignature();

	REQUIRE (dFlatMajor.isMajorKey());
	REQUIRE (dFlatMajor.getNumFlats() == 5);
	REQUIRE (dFlatMajor.getNumSharps() == 0);
	REQUIRE (dFlatMajor.getPitchClassOfRoot() == 1);

	const Mode cPhrygian { Mode::Type::Phrygian, PitchClass { 0 } };

	REQUIRE (cPhrygian.getNumFlats() == 4);
	REQUIRE (cPhrygian.getNumSharps() == 0);

	const auto aFlatMajor = cPhrygian.getKeySignature();

	REQUIRE (aFlatMajor.isMajorKey());
	REQUIRE (aFlatMajor.getNumFlats() == 4);
	REQUIRE (aFlatMajor.getNumSharps() == 0);
	REQUIRE (aFlatMajor.getPitchClassOfRoot() == 8);
}

TEST_CASE ("Mode - Lydian", TAGS)
{
	const Mode aLydian { Mode::Type::Lydian, PitchClass { 9 } };

	REQUIRE (aLydian.getNumFlats() == 0);
	REQUIRE (aLydian.getNumSharps() == 4);

	const auto eMajor = aLydian.getKeySignature();

	REQUIRE (eMajor.isMajorKey());
	REQUIRE (eMajor.getNumFlats() == 0);
	REQUIRE (eMajor.getNumSharps() == 4);
	REQUIRE (eMajor.getPitchClassOfRoot() == 4);

	const Mode eLydian { Mode::Type::Lydian, PitchClass { 4 } };

	REQUIRE (eLydian.getNumFlats() == 0);
	REQUIRE (eLydian.getNumSharps() == 5);

	const auto bMajor = eLydian.getKeySignature();

	REQUIRE (bMajor.isMajorKey());
	REQUIRE (bMajor.getNumFlats() == 0);
	REQUIRE (bMajor.getNumSharps() == 5);
	REQUIRE (bMajor.getPitchClassOfRoot() == 11);
}

TEST_CASE ("Mode - Mixolydian", TAGS)
{
	const Mode bFlatMixolydian { Mode::Type::Mixolydian, PitchClass { 10 } };

	REQUIRE (bFlatMixolydian.getNumFlats() == 3);
	REQUIRE (bFlatMixolydian.getNumSharps() == 0);

	const auto eFlatMajor = bFlatMixolydian.getKeySignature();

	REQUIRE (eFlatMajor.isMajorKey());
	REQUIRE (eFlatMajor.getNumFlats() == 3);
	REQUIRE (eFlatMajor.getNumSharps() == 0);
	REQUIRE (eFlatMajor.getPitchClassOfRoot() == 3);

	const Mode fSharpMixolydian { Mode::Type::Mixolydian, PitchClass { 6 } };

	REQUIRE ((fSharpMixolydian.getNumFlats() == 7 || fSharpMixolydian.getNumSharps() == 5));

	auto bMajor = fSharpMixolydian.getKeySignature();

	if (bMajor.isFlatKey())
		bMajor = bMajor.getEnharmonicKey();

	REQUIRE (bMajor.isMajorKey());
	REQUIRE (bMajor.getNumFlats() == 0);
	REQUIRE (bMajor.getNumSharps() == 5);
	REQUIRE (bMajor.getPitchClassOfRoot() == 11);

	//		bMajor = bMajor.getEnharmonicKey();
	//
	//		REQUIRE (bMajor.isMajorKey());
	//		REQUIRE (bMajor.getNumFlats() == 7);
	//		REQUIRE (bMajor.getNumSharps() == 0);
	//		REQUIRE (bMajor.getPitchClassOfRoot() == 11);
}

TEST_CASE ("Mode - Aeolian", TAGS)
{
	const Mode aAeolian { Mode::Type::Aeolian, PitchClass { 9 } };

	REQUIRE (aAeolian.getNumFlats() == 0);
	REQUIRE (aAeolian.getNumSharps() == 0);

	const auto aMinor = aAeolian.getKeySignature();

	REQUIRE (aMinor.isMinorKey());
	REQUIRE (aMinor.getNumFlats() == 0);
	REQUIRE (aMinor.getNumSharps() == 0);
	REQUIRE (aMinor.getPitchClassOfRoot() == 9);

	const Mode bFlatAeolian { Mode::Type::Aeolian, PitchClass { 10 } };

	REQUIRE (bFlatAeolian.getNumFlats() == 5);
	REQUIRE (bFlatAeolian.getNumSharps() == 0);

	const auto bFlatMinor = bFlatAeolian.getKeySignature();

	REQUIRE (bFlatMinor.isMinorKey());
	REQUIRE (bFlatMinor.getNumFlats() == 5);
	REQUIRE (bFlatMinor.getNumSharps() == 0);
	REQUIRE (bFlatMinor.getPitchClassOfRoot() == 10);
}

TEST_CASE ("Mode - Locrian", TAGS)
{
	const Mode bFlatLocrian { Mode::Type::Locrian, PitchClass { 10 } };

	REQUIRE (bFlatLocrian.getNumFlats() == 7);
	REQUIRE (bFlatLocrian.getNumSharps() == 0);

	const auto cFlatMajor = bFlatLocrian.getKeySignature();

	REQUIRE (cFlatMajor.isMajorKey());
	REQUIRE (cFlatMajor.getNumFlats() == 7);
	REQUIRE (cFlatMajor.getNumSharps() == 0);
	REQUIRE (cFlatMajor.getPitchClassOfRoot() == 11);

	const Mode fLocrian { Mode::Type::Locrian, PitchClass { 5 } };

	REQUIRE (fLocrian.getNumFlats() == 6);
	REQUIRE (fLocrian.getNumSharps() == 0);

	const auto gFlatMajor = fLocrian.getKeySignature();

	REQUIRE (gFlatMajor.isMajorKey());
	REQUIRE (gFlatMajor.getNumFlats() == 6);
	REQUIRE (gFlatMajor.getNumSharps() == 0);
	REQUIRE (gFlatMajor.getPitchClassOfRoot() == 6);
}

#undef TAGS
