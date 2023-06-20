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
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_PitchClass.h"
#include "lharmony/lharmony_Interval.h"

/** @file
	This file defines the tone row class.
	@ingroup limes_harmony
 */

namespace limes::harmony
{

/** This class represents a 12-tone sequence of pitch classes.

	@todo func to print to stream

	isInversionOf, isRetrogradeOf, isTranspositionOf

	@ingroup limes_harmony

	@todo random tone row generator
 */
class LHARM_EXPORT ToneRow final
{
public:

	using Pitches   = std::array<PitchClass, 12>;
	using Intervals = std::array<Interval, 11>;

	/**
		@throws std::runtime_error An exception will be thrown if the tone row
		contains duplicate pitch classes.
	 */
	explicit ToneRow (const Pitches& row);

	/**
		@throws std::runtime_error An exception will be thrown if the tone row
		contains duplicate pitch classes.
	 */
	ToneRow (PitchClass one,  PitchClass two, PitchClass three,  PitchClass four,
			 PitchClass five, PitchClass six, PitchClass seven,  PitchClass eight,
			 PitchClass nine, PitchClass ten, PitchClass eleven, PitchClass twelve);

	ToneRow (const ToneRow&) = default;
	ToneRow& operator= (const ToneRow&) = default;

	ToneRow (ToneRow&&) = default;
	ToneRow& operator= (ToneRow&&) = default;

	/** Returns the index in this tone row at which the specified pitch class is found.

		@see getPitchAtIndex()
	 */
	[[nodiscard]] size_t getIndexOfPitch (PitchClass pitch) const noexcept;

	/** Returns the pitch class in the tone row at the specified index.

		@throws std::out_of_range An exception will be thrown if the requested index
		is greater than 11.
	 */
	[[nodiscard]] PitchClass getPitchAtIndex (size_t index) const;

	/** Returns the pitch class in the tone row at the specified index.

		@throws std::out_of_range An exception will be thrown if the requested index
		is greater than 11.

		@see getPitchAtIndex(), getIndexOfPitch()
	 */
	PitchClass operator[](size_t index) const;

	/** Returns the underlying array of PitchClass objects.
		@see getIntervals()
	 */
	[[nodiscard]] const Pitches& getPitchClasses() const noexcept;

	/** Returns an array of intervals representing the intervals between this tone row's pitches.
		@see getPitchClasses()
	 */
	[[nodiscard]] Intervals getIntervals() const;

	/** Returns a tone row that is the inversion of this one. The new tone row will have
		the same first pitch class as this one, but every interval will be inverted -- if
		the original tone row began with an ascending major third (C up to E-flat), the new
		tone row will begin with a descending major third (C down to A-flat).

		@see retrogradeInversion()
	 */
	[[nodiscard]] ToneRow inversion() const;

	/** Returns a tone row that is this one, reversed.

		@see retrogradeInversion()
	 */
	[[nodiscard]] ToneRow retrograde() const;

	/** Returns a new tone row that is the inversion of this tone row's retrograde. This is
		the same as calling @verbatim inversion().retrograde() @endverbatim .

		@see inversion(), retrograde()
	 */
	[[nodiscard]] ToneRow retrogradeInversion() const;

	/** @name Transpositions
		Returns a new tone row that has the same intervals as this one, but starts on a different
		pitch class.
	 */
	///@{
	[[nodiscard]] ToneRow transposition (const Interval& interval, bool up) const;
	[[nodiscard]] ToneRow transposition (int numSemitones) const;
	///@}

	bool operator== (const ToneRow& other) const noexcept;
	bool operator!= (const ToneRow& other) const noexcept;

	using iterator               = Pitches::iterator;
	using const_iterator         = Pitches::const_iterator;
	using reverse_iterator       = Pitches::reverse_iterator;
	using const_reverse_iterator = Pitches::const_reverse_iterator;

	iterator begin() noexcept;
	iterator end() noexcept;

	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;

	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator rend() const noexcept;

private:

	void validatePitchClasses() const;

	Pitches pitches;
};

}
