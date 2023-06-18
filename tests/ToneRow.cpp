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

using limes::harmony::ToneRow;
using PC = limes::harmony::PitchClass;

#define TAGS "[audio][harmony][ToneRow]"

[[nodiscard]] static inline ToneRow getAscendingChromaticToneRow()
{
	return ToneRow { PC(0), PC(1), PC(2), PC(3), PC(4), PC(5), PC(6), PC(7), PC(8), PC(9), PC(10), PC(11) };
}

[[nodiscard]] static inline ToneRow getDescendingChromaticToneRow()
{
	return ToneRow { PC(11), PC(10), PC(9), PC(8), PC(7), PC(6), PC(5), PC(4), PC(3), PC(2), PC(1), PC(0) };
}

TEST_CASE ("ToneRow - inversion", TAGS)
{
	SECTION ("Ascending")
	{
		const auto orig = getAscendingChromaticToneRow();

		const auto inv = orig.inversion();

		REQUIRE (inv[0UL] == orig[0UL]);

		REQUIRE (inv.inversion() == orig);

		REQUIRE (inv[1UL] == PC(11));
		REQUIRE (inv[2UL] == PC(10));
		REQUIRE (inv[3UL] == PC(9));
		REQUIRE (inv[4UL] == PC(8));
		REQUIRE (inv[5UL] == PC(7));
		REQUIRE (inv[6UL] == PC(6));
		REQUIRE (inv[7UL] == PC(5));
		REQUIRE (inv[8UL] == PC(4));
		REQUIRE (inv[9UL] == PC(3));
		REQUIRE (inv[10UL] == PC(2));
		REQUIRE (inv[11UL] == PC(1));
	}

	 SECTION ("Descending")
	 {
		 const auto orig = getDescendingChromaticToneRow();

		 const auto inv = orig.inversion();

		 REQUIRE (inv[0UL] == orig[0UL]);

		 REQUIRE (inv.inversion() == orig);

		 REQUIRE (inv[1UL] == PC(0));
		 REQUIRE (inv[2UL] == PC(1));
		 REQUIRE (inv[3UL] == PC(2));
		 REQUIRE (inv[4UL] == PC(3));
		 REQUIRE (inv[5UL] == PC(4));
		 REQUIRE (inv[6UL] == PC(5));
		 REQUIRE (inv[7UL] == PC(6));
		 REQUIRE (inv[8UL] == PC(7));
		 REQUIRE (inv[9UL] == PC(8));
		 REQUIRE (inv[10UL] == PC(9));
		 REQUIRE (inv[11UL] == PC(10));
	 }
}

TEST_CASE ("ToneRow - retrograde", TAGS)
{
	SECTION ("Ascending")
	{
		const auto orig = getAscendingChromaticToneRow();

		const auto ret = orig.retrograde();

		REQUIRE (ret.retrograde() == orig);

		REQUIRE (ret[0UL] == PC(11));
		REQUIRE (ret[1UL] == PC(10));
		REQUIRE (ret[2UL] == PC(9));
		REQUIRE (ret[3UL] == PC(8));
		REQUIRE (ret[4UL] == PC(7));
		REQUIRE (ret[5UL] == PC(6));
		REQUIRE (ret[6UL] == PC(5));
		REQUIRE (ret[7UL] == PC(4));
		REQUIRE (ret[8UL] == PC(3));
		REQUIRE (ret[9UL] == PC(2));
		REQUIRE (ret[10UL] == PC(1));
		REQUIRE (ret[11UL] == PC(0));
	}

	SECTION ("Descending")
	{
		const auto orig = getDescendingChromaticToneRow();

		const auto ret = orig.retrograde();

		REQUIRE (ret.retrograde() == orig);

		REQUIRE (ret[0UL] == PC(0));
		REQUIRE (ret[1UL] == PC(1));
		REQUIRE (ret[2UL] == PC(2));
		REQUIRE (ret[3UL] == PC(3));
		REQUIRE (ret[4UL] == PC(4));
		REQUIRE (ret[5UL] == PC(5));
		REQUIRE (ret[6UL] == PC(6));
		REQUIRE (ret[7UL] == PC(7));
		REQUIRE (ret[8UL] == PC(8));
		REQUIRE (ret[9UL] == PC(9));
		REQUIRE (ret[10UL] == PC(10));
		REQUIRE (ret[11UL] == PC(11));
	}
}

TEST_CASE ("ToneRow - transposition", TAGS)
{
	const auto orig = getAscendingChromaticToneRow();

	const auto up = orig.transposition (1);

	REQUIRE (up.transposition (-1) == orig);
}

TEST_CASE ("ToneRow - retrograde inversion", TAGS)
{
	const auto orig = getAscendingChromaticToneRow();

	const auto inv = orig.retrogradeInversion();

	REQUIRE (orig.inversion().retrograde() == inv);

	REQUIRE (inv[0UL] == PC(1));
	REQUIRE (inv[1UL] == PC(2));
	REQUIRE (inv[2UL] == PC(3));
	REQUIRE (inv[3UL] == PC(4));
	REQUIRE (inv[4UL] == PC(5));
	REQUIRE (inv[5UL] == PC(6));
	REQUIRE (inv[6UL] == PC(7));
	REQUIRE (inv[7UL] == PC(8));
	REQUIRE (inv[8UL] == PC(9));
	REQUIRE (inv[9UL] == PC(10));
	REQUIRE (inv[10UL] == PC(11));
	REQUIRE (inv[11UL] == PC(0));
}

static inline ToneRow getInvalidRow()
{
	return ToneRow { PC(0), PC(0), PC(2), PC(3), PC(4), PC(5), PC(6), PC(7), PC(8), PC(9), PC(10), PC(11) };
}

TEST_CASE ("ToneRow - test throws", TAGS)
{
	const auto row = getAscendingChromaticToneRow();

	REQUIRE_THROWS (row[12UL]);

	REQUIRE_THROWS (getInvalidRow());
}
