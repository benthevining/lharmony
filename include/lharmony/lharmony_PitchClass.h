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

#pragma once

#include <array>
#include <string_view>
#include <iostream>
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_PitchUtils.h"

/** @file
	This file defines the PitchClass class.

	@ingroup limes_harmony
 */

namespace limes::harmony
{

/** A struct that represents a %pitch class.
	This class is agnostic to the octave the %pitch class appears in, and also to enharmonic spellings -- thus, C-sharp and D-flat are considered the same %pitch class.
	A %pitch class is represented as an integer between 0 and 11, with 0 being C, 1 being C-sharp/D-flat, and 11 being B natural.

	Here are all possible %pitch classes:

	Integer value | Note name
	------------- | -----------------
	0             | C
	1             | C-sharp / D-flat
	2             | D
	3             | D-sharp / E-flat
	4             | E
	5             | F
	6             | F-sharp / G-flat
	7             | G
	8             | G-sharp / A-flat
	9             | A
	10            | A-sharp / B-flat
	11            | B

	@ingroup limes_harmony
	@see Pitch

	@todo to/from string
	@todo get solfege syllable
	@todo provide literals?
 */
struct LHARM_EXPORT PitchClass final
{
	/** Creates a %pitch class from an integer, where 0 is C, 1 is C#/Db, and 11 is B.
	 */
	constexpr explicit PitchClass (int midiPitch) noexcept
		: pitchClass (midiPitch % semitonesInOctave)
	{
	}

	constexpr PitchClass (const PitchClass&) = default;
	constexpr PitchClass& operator=(const PitchClass&) = default;

	constexpr PitchClass (PitchClass&&) = default;
	constexpr PitchClass& operator=(PitchClass&&) = default;

	/** Returns true if the two %pitch classes are equal. */
	[[nodiscard]] constexpr bool operator== (const PitchClass& other) const noexcept
	{
		return pitchClass == other.pitchClass;
	}

	/** Returns true if the two %pitch classes are not equal. */
	[[nodiscard]] constexpr bool operator!= (const PitchClass& other) const noexcept
	{
		return pitchClass != other.pitchClass;
	}

	constexpr PitchClass& operator+= (int numSemitones) noexcept
	{
		pitchClass = (pitchClass + numSemitones) % semitonesInOctave;
		return *this;
	}

	constexpr PitchClass& operator-= (int numSemitones) noexcept
	{
		pitchClass = (pitchClass - numSemitones) % semitonesInOctave;
		return *this;
	}

	/** Returns true if this %pitch class represents a black key on a standard keyboard. */
	[[nodiscard]] constexpr bool isBlackKey() const noexcept
	{
		return pitchClass == 1 || pitchClass == 3 || pitchClass == 6 || pitchClass == 8 || pitchClass == 10;
	}

	/** Returns true if this %pitch class represents a white key on a standard keyboard. */
	[[nodiscard]] constexpr bool isWhiteKey() const noexcept
	{
		return ! isBlackKey();
	}

	/** Returns this %pitch class as an integer between 0 and 11, where 0 is C and 11 is B. */
	constexpr operator int() const noexcept
	{
		return pitchClass;
	}

	/** Returns this %pitch class as an integer between 0 and 11, where 0 is C and 11 is B. */
	[[nodiscard]] constexpr int getAsInt() const noexcept
	{
		return pitchClass;
	}

	/** Returns a string description of this pitch class. */
	[[nodiscard]] std::string_view getString (bool useSharps = true) const noexcept;

	/** Returns an iterable list of all the %pitch classes, starting from 0 and ending with 11. */
	[[nodiscard]] static constexpr std::array<PitchClass, 12> getAll()
	{
		using PC = PitchClass;
		return { PC { 0 }, PC { 1 }, PC { 2 }, PC { 3 }, PC { 4 }, PC { 5 }, PC { 6 }, PC { 7 }, PC { 8 }, PC { 9 }, PC { 10 }, PC { 11 } };
	}

private:
	int pitchClass { 0 };
};

/** Writes a string description of the PitchClass to the output stream.

	@ingroup music_harmony
	@relates PitchClass
	@see PitchClass::getString()
 */
LHARM_EXPORT std::ostream& operator<< (std::ostream& os, const PitchClass& value);

}  // namespace limes::harmony
