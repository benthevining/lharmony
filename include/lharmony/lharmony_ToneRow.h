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

	@todo docs
	@todo func to print to stream

	isInversionOf, isRetrogradeOf, isTranspositionOf

	@ingroup limes_harmony
 */
class LHARM_EXPORT ToneRow final
{
public:

	using Pitches = std::array<PitchClass, 12>;

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

	[[nodiscard]] size_t getIndexOfPitch (PitchClass pitch) const noexcept;

	/**
		@throws std::out_of_range An exception will be thrown if the requested index
		is greater than 11.
	 */
	[[nodiscard]] PitchClass getPitchAtIndex (size_t index) const;

	/**
		@throws std::out_of_range An exception will be thrown if the requested index
		is greater than 11.
	 */
	PitchClass operator[](size_t index) const;

	[[nodiscard]] const Pitches& getPitchClasses() const noexcept;

	[[nodiscard]] ToneRow inversion() const;

	[[nodiscard]] ToneRow retrograde() const;

	[[nodiscard]] ToneRow retrogradeInversion() const;

	[[nodiscard]] ToneRow transposition (const Interval& interval, bool up) const;
	[[nodiscard]] ToneRow transposition (int numSemitones) const;

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
