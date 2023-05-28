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

using limes::harmony::Interval;
namespace i = limes::harmony::intervals;

#define TAGS "[audio][harmony][interval]"

TEST_CASE ("Interval - valid qualities/kinds", TAGS)
{
	STATIC_REQUIRE (! Interval::isValidQualityForKind (Interval::Quality::Major, 4));
	STATIC_REQUIRE (! Interval::isValidQualityForKind (Interval::Quality::Minor, 5));
	STATIC_REQUIRE (! Interval::isValidQualityForKind (Interval::Quality::Perfect, 2));
	STATIC_REQUIRE (! Interval::isValidQualityForKind (Interval::Quality::Perfect, 6));
	STATIC_REQUIRE (! Interval::isValidQualityForKind (Interval::Quality::Diminished, 0));
	STATIC_REQUIRE (Interval::isValidQualityForKind (Interval::Quality::Augmented, 8));

	for (auto kind = 2; kind <= 8; ++kind)
	{
		REQUIRE (Interval::isValidQualityForKind (Interval::Quality::Diminished, kind));
		REQUIRE (Interval::isValidQualityForKind (Interval::Quality::Augmented, kind));
	}
}

TEST_CASE ("Interval - inverse", TAGS)
{
	auto test_inverse = [] (const Interval& interval1, const Interval& interval2)
	{
		REQUIRE (interval1.getInverse() == interval2);
		REQUIRE (interval2.getInverse() == interval1);
		REQUIRE (interval1.getNumSemitones() + interval2.getNumSemitones() == 12);

		REQUIRE (interval1 + interval2 == i::perfect::octave);
		REQUIRE ((i::perfect::octave - interval1).isEnharmonicTo (interval2));
		REQUIRE ((i::perfect::octave - interval2).isEnharmonicTo (interval1));
	};

	test_inverse (i::perfect::unison, i::perfect::octave);
	test_inverse (i::augmented::unison, i::diminished::octave);
	test_inverse (i::diminished::second, i::augmented::seventh);
	test_inverse (i::minor::second, i::major::seventh);
	test_inverse (i::major::second, i::minor::seventh);
	test_inverse (i::augmented::second, i::diminished::seventh);
	test_inverse (i::diminished::third, i::augmented::sixth);
	test_inverse (i::minor::third, i::major::sixth);
	test_inverse (i::major::third, i::minor::sixth);
	test_inverse (i::augmented::third, i::diminished::sixth);
	test_inverse (i::diminished::fourth, i::augmented::fifth);
	test_inverse (i::perfect::fourth, i::perfect::fifth);
	test_inverse (i::augmented::fourth, i::diminished::fifth);
	test_inverse (i::diminished::fifth, i::augmented::fourth);
	test_inverse (i::perfect::fifth, i::perfect::fourth);
	test_inverse (i::augmented::fifth, i::diminished::fourth);
	test_inverse (i::diminished::sixth, i::augmented::third);
	test_inverse (i::minor::sixth, i::major::third);
	test_inverse (i::major::sixth, i::minor::third);
	test_inverse (i::augmented::sixth, i::diminished::third);
	test_inverse (i::diminished::seventh, i::augmented::second);
	test_inverse (i::minor::seventh, i::major::second);
	test_inverse (i::major::seventh, i::minor::second);
	test_inverse (i::augmented::seventh, i::diminished::second);
	test_inverse (i::diminished::octave, i::augmented::unison);
	test_inverse (i::perfect::octave, i::perfect::unison);

	// TODO: test augmented octave
}

TEST_CASE ("Interval - from semitones", TAGS)
{
	auto test_from_semitones = [] (int semitones, const Interval& expected)
	{
		REQUIRE (Interval::fromNumSemitones (semitones) == expected);
	};

	test_from_semitones (0, i::perfect::unison);
	test_from_semitones (1, i::minor::second);
	test_from_semitones (2, i::major::second);
	test_from_semitones (3, i::minor::third);
	test_from_semitones (4, i::major::third);
	test_from_semitones (5, i::perfect::fourth);
	test_from_semitones (6, i::augmented::fourth);
	test_from_semitones (7, i::perfect::fifth);
	test_from_semitones (8, i::minor::sixth);
	test_from_semitones (9, i::major::sixth);
	test_from_semitones (10, i::minor::seventh);
	test_from_semitones (11, i::major::seventh);
	test_from_semitones (12, i::perfect::octave);
	test_from_semitones (13, i::augmented::octave);
}

TEST_CASE ("Interval - increment", TAGS)
{
	auto test_increment = [] (Interval orig, const Interval& expected)
	{
		REQUIRE (orig < expected);
		REQUIRE (expected > orig);

		++orig;

		REQUIRE (orig == expected);
	};

	test_increment (i::perfect::unison, i::augmented::unison);
	test_increment (i::augmented::unison, i::major::second);
	test_increment (i::diminished::second, i::minor::second);
	test_increment (i::minor::second, i::major::second);
	test_increment (i::major::second, i::augmented::second);
	test_increment (i::augmented::second, i::major::third);
	test_increment (i::diminished::third, i::minor::third);
	test_increment (i::minor::third, i::major::third);
	test_increment (i::major::third, i::augmented::third);
	test_increment (i::augmented::third, i::augmented::fourth);
	test_increment (i::diminished::fourth, i::perfect::fourth);
	test_increment (i::perfect::fourth, i::augmented::fourth);
	test_increment (i::augmented::fourth, i::perfect::fifth);
	test_increment (i::diminished::fifth, i::perfect::fifth);
	test_increment (i::perfect::fifth, i::augmented::fifth);
	test_increment (i::augmented::fifth, i::major::sixth);
	test_increment (i::diminished::sixth, i::minor::sixth);
	test_increment (i::minor::sixth, i::major::sixth);
	test_increment (i::major::sixth, i::augmented::sixth);
	test_increment (i::augmented::sixth, i::major::seventh);
	test_increment (i::diminished::seventh, i::minor::seventh);
	test_increment (i::minor::seventh, i::major::seventh);
	test_increment (i::major::seventh, i::augmented::seventh);
	test_increment (i::diminished::octave, i::perfect::octave);
	test_increment (i::perfect::octave, i::augmented::octave);
}

TEST_CASE ("Interval - decrement", TAGS)
{
	auto test_decrement = [] (Interval orig, const Interval& expected)
	{
		REQUIRE (orig > expected);
		REQUIRE (expected < orig);

		--orig;

		REQUIRE (orig == expected);
	};

	test_decrement (i::augmented::unison, i::perfect::unison);
	test_decrement (i::diminished::second, i::perfect::unison);	 // special case
	test_decrement (i::minor::second, i::diminished::second);
	test_decrement (i::major::second, i::minor::second);
	test_decrement (i::augmented::second, i::major::second);
	test_decrement (i::diminished::third, i::minor::second);
	test_decrement (i::minor::third, i::diminished::third);
	test_decrement (i::major::third, i::minor::third);
	test_decrement (i::augmented::third, i::major::third);
	test_decrement (i::diminished::fourth, i::minor::third);
	test_decrement (i::perfect::fourth, i::diminished::fourth);
	test_decrement (i::augmented::fourth, i::perfect::fourth);
	test_decrement (i::diminished::fifth, i::perfect::fourth);
	test_decrement (i::perfect::fifth, i::diminished::fifth);
	test_decrement (i::augmented::fifth, i::perfect::fifth);
	test_decrement (i::diminished::sixth, i::diminished::fifth);
	test_decrement (i::minor::sixth, i::diminished::sixth);
	test_decrement (i::major::sixth, i::minor::sixth);
	test_decrement (i::augmented::sixth, i::major::sixth);
	test_decrement (i::diminished::seventh, i::minor::sixth);
	test_decrement (i::minor::seventh, i::diminished::seventh);
	test_decrement (i::major::seventh, i::minor::seventh);
	test_decrement (i::augmented::seventh, i::major::seventh);
	test_decrement (i::diminished::octave, i::minor::seventh);
	test_decrement (i::perfect::octave, i::diminished::octave);
	test_decrement (i::augmented::octave, i::perfect::octave);

	// special case
	auto unison = i::perfect::unison;
	--unison;
	REQUIRE (unison == i::perfect::unison);
}

TEST_CASE ("Interval - enharmonics", TAGS)
{
	auto test_enharmonic = [] (const Interval& interval1, const Interval& interval2, int numSemitones)
	{
		REQUIRE (interval1.getNumSemitones() == interval2.getNumSemitones());

		REQUIRE (interval1.isEnharmonicTo (interval2));
		REQUIRE (interval2.isEnharmonicTo (interval1));

		REQUIRE (interval1.getCents_EqualTemperament() == interval2.getCents_EqualTemperament());

		REQUIRE (interval1.getNumSemitones() == numSemitones);

		REQUIRE (Interval::isValidQualityForKind (interval1.getQuality(), interval1.getKind()));
		REQUIRE (Interval::isValidQualityForKind (interval2.getQuality(), interval2.getKind()));
	};

	test_enharmonic (i::perfect::unison, i::diminished::second, 0);
	test_enharmonic (i::augmented::unison, i::minor::second, 1);
	test_enharmonic (i::major::second, i::diminished::third, 2);
	test_enharmonic (i::minor::third, i::augmented::second, 3);
	test_enharmonic (i::major::third, i::diminished::fourth, 4);
	test_enharmonic (i::perfect::fourth, i::augmented::third, 5);
	test_enharmonic (i::augmented::fourth, i::diminished::fifth, 6);
	test_enharmonic (i::perfect::fifth, i::diminished::sixth, 7);
	test_enharmonic (i::minor::sixth, i::augmented::fifth, 8);
	test_enharmonic (i::major::sixth, i::diminished::seventh, 9);
	test_enharmonic (i::minor::seventh, i::augmented::sixth, 10);
	test_enharmonic (i::major::seventh, i::diminished::octave, 11);
	test_enharmonic (i::perfect::octave, i::augmented::seventh, 12);

	// special case
	REQUIRE (i::augmented::octave.getNumSemitones() == 13);
}

#undef TAGS
