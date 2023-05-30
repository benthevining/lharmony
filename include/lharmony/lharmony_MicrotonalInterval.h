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

#include <cmath>
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_Pitch.h"

/** @file
	This file defines the \c MicrotonalInterval class.

	@ingroup lharmony_intervals
 */

namespace limes::harmony
{

/** A class that can represent intervals that are not whole numbers of semitones.

	@see Interval, CompoundInterval

	@todo operator<< for std::ostream (toString method)
 */
class LHARM_EXPORT MicrotonalInterval final
{
public:
	constexpr explicit MicrotonalInterval (double numSemitones)
		: semitones (numSemitones)
	{
	}

	constexpr MicrotonalInterval (const MicrotonalInterval&)			= default;
	constexpr MicrotonalInterval& operator= (const MicrotonalInterval&) = default;

	constexpr MicrotonalInterval (MicrotonalInterval&&)			   = default;
	constexpr MicrotonalInterval& operator= (MicrotonalInterval&&) = default;

	~MicrotonalInterval() = default;

	/** Returns true if these two microtonal intervals represent the same fractional amount of semitones. */
	[[nodiscard]] constexpr bool operator== (const MicrotonalInterval& other) const noexcept
	{
		return semitones == other.semitones;
	}

	/** Returns true if these two microtonal intervals do not represent the same fractional amount of semitones. */
	[[nodiscard]] constexpr bool operator!= (const MicrotonalInterval& other) const noexcept
	{
		return semitones != other.semitones;
	}

	/** Returns true if this microtonal %interval is larger than the other one. */
	[[nodiscard]] inline bool operator> (const MicrotonalInterval& other) const noexcept
	{
		return std::abs (semitones) > std::abs (other.semitones);
	}

	/** Returns true if this microtonal %interval is smaller than the other one. */
	[[nodiscard]] inline bool operator<(const MicrotonalInterval& other) const noexcept
	{
		return std::abs (semitones) < std::abs (other.semitones);
	}

	/** Returns the number of cents this microtonal %interval would represent in equal temperament. */
	[[nodiscard]] constexpr double getCents() const noexcept
	{
		return semitones * 100.;
	}

	/** Returns the number of semitones this microtonal %interval represents. */
	[[nodiscard]] constexpr double getSemitones() const noexcept
	{
		return semitones;
	}

	/** Returns a new pitch object that represents the note this interval's distance above or below the passed pitch object.
		@param other The pitch object to start from.
		@param above When true, the returned pitch will be this interval's distance above the passed pitch. When false, the returned pitch will be this interval's distance below the passed pitch.
	 */
	[[nodiscard]] constexpr Pitch applyToPitch (Pitch other, bool above) const noexcept
	{
		if (above)
			return Pitch { other.getMidiPitch() + semitones };

		return Pitch { other.getMidiPitch() - semitones };
	}

private:
	double semitones { 0. };
};


/** Adds an interval to the given pitch and returns a new pitch object at the resulting pitch.
	@ingroup music_intervals
 */
LHARM_EXPORT constexpr Pitch operator+ (const Pitch& pitch, const MicrotonalInterval& interval) noexcept
{
	return Pitch { pitch.getMidiPitch() + interval.getSemitones() };
}

/** Subtracts an interval from the given pitch and returns a new pitch object at the resulting pitch.
	@ingroup music_intervals
 */
LHARM_EXPORT constexpr Pitch operator- (const Pitch& pitch, const MicrotonalInterval& interval) noexcept
{
	return Pitch { pitch.getMidiPitch() - interval.getSemitones() };
}

}  // namespace limes::harmony
