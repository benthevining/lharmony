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

#include <ostream>
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_PitchClass.h"
#include "lharmony/lharmony_PitchUtils.h"

/** @file
	This file defines the \c Pitch class.

	@ingroup limes_harmony
 */

namespace limes::harmony
{

class Interval;

/** This class represents a specific pitch.

	This class is essentially a simple wrapper around a MIDI %pitch, with some convenient functions for representing it certain ways.
	This class is agnostic to enharmonic spellings.

	@ingroup limes_harmony
	@see PitchClass
 */
class LHARM_EXPORT Pitch final
{
public:
	/** @name Constructors */
	///@{
	/** Creates a %pitch object from a MIDI %pitch, which can be passed to the constructor as any scalar arithmetic type.

		@see fromMIDI()
	 */
	template <ArithmeticType T>
	constexpr explicit Pitch (T midiNote) noexcept
		: midiPitch (static_cast<double> (midiNote))
	{
	}

	/** Creates a %pitch object from a %pitch class and a MIDI octave number.
		@see lowestNoteOfMidiOctave()
	 */
	constexpr Pitch (const PitchClass& pitchClass, int midiOctave) noexcept
		: Pitch (lowestNoteOfMidiOctave (midiOctave) + pitchClass.getAsInt())
	{
	}

	constexpr Pitch (const Pitch&) = default;
	constexpr Pitch& operator=(const Pitch&) = default;

	constexpr Pitch (Pitch&&) = default;
	constexpr Pitch& operator=(Pitch&&) = default;

	/** Creates a Pitch object from a frequency in Hz.

		@see fromMIDI(), fromPitchClass()
	 */
	template <ArithmeticType T>
	[[nodiscard]] static constexpr Pitch fromFreq (T freqHz) noexcept
	{
		return Pitch { freqToMidi (freqHz) };
	}

	/** Creates a Pitch object from a MIDI note number.
		This is the same as the single-argument constructor, but a bit more explicit with the
		fact that the argument is a MIDI note number.

		@see fromFreq(), fromPitchClass()
	 */
	template <ArithmeticType T>
	[[nodiscard]] static constexpr Pitch fromMIDI (T midiNote) noexcept
	{
		return Pitch { midiNote };
	}

	/** Creates a Pitch object from a PitchClass and a MIDI octave number.

		@see fromFreq(), fromMIDI()
	 */
	template <ArithmeticType T>
	[[nodiscard]] static constexpr Pitch fromPitchClass (PitchClass pitchClass, T midiOctave) noexcept
	{
		const Pitch p { pitchClass.getAsInt() };
		return p.inOctave (static_cast<int> (midiOctave));
	}

	///@}

	/** @name Equality comparisons */
	///@{
	/** Returns true if the two %pitch objects are exactly equal. */
	[[nodiscard]] constexpr bool operator== (const Pitch& other) const noexcept
	{
		return midiPitch == other.midiPitch;
	}

	/** Returns true if the two %pitch objects are not exactly equal. */
	[[nodiscard]] constexpr bool operator!= (const Pitch& other) const noexcept
	{
		return midiPitch != other.midiPitch;
	}

	/** Returns true if the two %pitch objects round to the same nearest MIDI note. */
	[[nodiscard]] bool approximatelyEqual (Pitch other) const noexcept;
	///@}

	/** Returns true if this %pitch is higher than the other one. */
	[[nodiscard]] constexpr bool operator> (const Pitch& other) const noexcept
	{
		return midiPitch > other.midiPitch;
	}

	/** Returns true if this %pitch is lower than the other one. */
	[[nodiscard]] constexpr bool operator<(const Pitch& other) const noexcept
	{
		return midiPitch < other.midiPitch;
	}

	/** Returns the difference between this and another %pitch as an Interval object. */
	[[nodiscard]] Interval operator- (const Pitch& other) const noexcept;

	/** Returns this %pitch as a frequency in Hz.
		@see math::midiToFreq()
	 */
	[[nodiscard]] double getFreqHz() const noexcept;

	/** Returns this %pitch as a frequency in Hz, rounded to the nearest integer.
	 */
	[[nodiscard]] int getRoundedFreqHz() const noexcept;

	/** Returns the MIDI %pitch that this %pitch object represents. */
	[[nodiscard]] constexpr double getMidiPitch() const noexcept
	{
		return midiPitch;
	}

	/** Returns this %pitch object's MIDI pitch, rounded to the nearest integer MIDI note. */
	[[nodiscard]] int getRoundedMidiPitch() const noexcept;

	/** Returns this %pitch object's %pitch class.
		@see PitchClass
	 */
	[[nodiscard]] PitchClass getPitchClass() const noexcept;

	/** Returns this %pitch object's MIDI octave number.
		@see octaveNumberOfMidiNote()
	 */
	[[nodiscard]] int getOctaveNumber() const noexcept;

	/** Returns true if this pitch's nearest integer MIDI note is a black key on a standard keyboard. */
	[[nodiscard]] bool isBlackKey() const noexcept;

	/** Returns true if this pitch's nearest integer MIDI note is a white key on a standard keyboard. */
	[[nodiscard]] bool isWhiteKey() const noexcept;

	/** Returns true if this %pitch does not correspond exactly with any of the keys on a piano tuned to equal temperament.
	 */
	[[nodiscard]] bool isMicrotone() const noexcept;

	/** Returns the %pitch class of this %pitch, in the desired MIDI octave. */
	[[nodiscard]] Pitch inOctave (int octaveNumber) const noexcept;

private:
	double midiPitch { 60. };
};

/** Writes the MIDI pitch of the given Pitch object to the output stream.

	@ingroup music_harmony
	@relates Pitch
 */
LHARM_EXPORT std::ostream& operator<< (std::ostream& os, const Pitch& value);

}  // namespace limes::harmony
