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

#include <vector>
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_Scale.h"
#include "lharmony/lharmony_PitchClass.h"

/** @file
	This file defines the WholeTone %scale class.

	@ingroup lharmony_scales
 */

namespace limes::harmony::scales
{

/** A class that represents a whole tone %scale.
	Whole tone scale objects only differ from one another by their starting %pitch.

	@ingroup lharmony_scales
 */
class LHARM_EXPORT WholeTone final : public Scale
{
public:
	/** @name Constructors */
	///@{

	/** Creates a whole tone %scale object with the given %pitch class as its root. */
	constexpr explicit WholeTone (PitchClass pitchClassOfRoot) noexcept
		: startingPitchClass (pitchClassOfRoot)
	{
	}

	/** Creates a whole tone %scale starting on the given MIDI note. */
	constexpr explicit WholeTone (int rootNote) noexcept
		: startingPitchClass (rootNote)
	{
	}

	///@}

	WholeTone (const WholeTone&) = default;
	WholeTone& operator=(const WholeTone&) = default;

	WholeTone (WholeTone&&) = default;
	WholeTone& operator=(WholeTone&&) = default;

	/** Returns true if the other whole tone %scale has the same root as this one. */
	[[nodiscard]] bool operator== (const WholeTone& other) const;

	/** Returns true if the other whole tone %scale does not have the same root as this one. */
	[[nodiscard]] bool operator!= (const WholeTone& other) const;

	/** Returns an array of 6 2's, since every %interval in this %scale is a whole step. */
	[[nodiscard]] std::vector<int> getIntervalsAsSemitones() const final;

	/** Returns the %pitch class of the root of this %scale. */
	[[nodiscard]] PitchClass getPitchClassOfRoot() const noexcept final;

	/** Returns 6. */
	[[nodiscard]] int notesPerOctave() const noexcept final;

private:
	PitchClass startingPitchClass { 0 };
};

}  // namespace limes::harmony::scales
