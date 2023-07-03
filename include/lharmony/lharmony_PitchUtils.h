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
#include <cassert>
#include <type_traits>
#include <cmath>
#include "lharmony/lharmony_Export.h"

/** @file
	This file contains miscellaneous pitch utilities.

	@ingroup limes_harmony
 */

namespace limes::harmony
{

/** @ingroup limes_harmony
	@{
 */

/** Integer constant representing the number of semitones in an octave (12). */
LHARM_EXPORT constinit const auto semitonesInOctave = 12;

/** Returns the octave number of a given MIDI pitch.

	The formula is @f$ O=\lfloor\frac{note}{12}-1\rfloor @f$.
	This formula puts note 69 in octave 4.

	Here are the MIDI octaves, as defined by this formula:

	Octave number | Note number range | Pitch range
	------------- | ----------------- | ------------
	0             | 12 - 23           | C0 - B0
	1             | 24 - 35           | C1 - B1
	2             | 36 - 47           | C2 - B2
	3             | 48 - 59           | C3 - B3
	4             | 60 - 71           | C4 - B4
	5             | 72 - 83           | C5 - B5
	6             | 84 - 95           | C6 - B6
	7             | 96 - 107          | C7 - B7

	@see lowestNoteOfMidiOctave
 */
LHARM_EXPORT inline int octaveNumberOfMidiNote (int midiNote) noexcept
{
	return static_cast<int> (std::floor (static_cast<float> (midiNote) / 12.f - 1.f));
}

/** Returns the lowest note of a given MIDI octave number (that octave's C key).

	The formula is @f$ note=(O+1)*12 @f$.
	This formula puts 60 as the lowest note of octave 4.

	Here are the MIDI octaves, as defined by this formula:

	Octave number | Note number range | Pitch range
	------------- | ----------------- | ------------
	0             | 12 - 23           | C0 - B0
	1             | 24 - 35           | C1 - B1
	2             | 36 - 47           | C2 - B2
	3             | 48 - 59           | C3 - B3
	4             | 60 - 71           | C4 - B4
	5             | 72 - 83           | C5 - B5
	6             | 84 - 95           | C6 - B6
	7             | 96 - 107          | C7 - B7

	@see octaveNumberOfMidiNote, highestNoteOfMidiOctave
 */
LHARM_EXPORT constexpr int lowestNoteOfMidiOctave (int octaveNumber) noexcept
{
	return (octaveNumber + 1) * 12;
}

/** Returns the highest note of a given MIDI octave number (that octave's B key).

	The formula is @f$ note=(O+1)*12+11 @f$.
	This formula puts 71 as the highest note of octave 4.

	Here are the MIDI octaves, as defined by this formula:

	Octave number | Note number range | Pitch range
	------------- | ----------------- | ------------
	0             | 12 - 23           | C0 - B0
	1             | 24 - 35           | C1 - B1
	2             | 36 - 47           | C2 - B2
	3             | 48 - 59           | C3 - B3
	4             | 60 - 71           | C4 - B4
	5             | 72 - 83           | C5 - B5
	6             | 84 - 95           | C6 - B6
	7             | 96 - 107          | C7 - B7

	@see octaveNumberOfMidiNote, lowestNoteOfMidiOctave
 */
LHARM_EXPORT constexpr int highestNoteOfMidiOctave (int octaveNumber) noexcept
{
	return lowestNoteOfMidiOctave (octaveNumber) + 11;
}

/** A utility concept that specifies the type must be an arithmetic type.
 */
template <typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

/** Converts a MIDI note to a frequency in Hz.
	The formula is @f$ f=440*2^{\frac{midiNote-69}{12}} @f$.
	@see freqToMidi
 */
template <ArithmeticType T>
[[nodiscard]] LHARM_EXPORT inline double midiToFreq (T midiNote) noexcept
{
	const auto exponent = (static_cast<double> (midiNote) - 69.) / 12.;

	return std::pow (2., exponent) * 440.;
}

/** Converts a frequency in Hz to a MIDI note.
	The formula is @f$ midi=69+12*\log_2\frac{freqHz}{440} @f$.
	@see midiToFreq
 */
template <ArithmeticType T>
[[nodiscard]] LHARM_EXPORT inline double freqToMidi (T freqHz) noexcept
{
	return 69. + 12. * std::log2 (static_cast<double> (freqHz) / 440.);
}

/** @} */

}  // namespace limes::harmony
