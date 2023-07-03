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

#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_Pitch.h"
#include "lharmony/lharmony_CompoundInterval.h"

/** @file
	This file defines the OvertoneSeries class.
	@ingroup limes_harmony
 */

namespace limes::harmony
{

/** This class represents an overtone series based on a specific fundamental frequency.

	@ingroup limes_harmony

	@todo UndertoneSeries class
 */
struct LHARM_EXPORT OvertoneSeries final
{
public:
	/** Creates an overtone series with the specified fundamental pitch. */
	constexpr explicit OvertoneSeries (Pitch fundamentalToUse) noexcept
		: fundamental (fundamentalToUse) { }

	/** Returns this overtone series's fundamental pitch. */
	[[nodiscard]] constexpr Pitch getFundamental() const noexcept { return fundamental; }

	/** Returns a specified harmonic of this overtone series. */
	[[nodiscard]] inline Pitch getHarmonic (size_t degree) const noexcept
	{
		if (degree == 0UL)
			return fundamental;

		const auto degFactor = static_cast<double>(degree) + 1.;

		return Pitch::fromFreq (fundamental.getFreqHz() * degFactor);
	}

	inline Pitch operator[](size_t degree) const noexcept
	{
		return getHarmonic (degree);
	}

	/** Returns an Interval object representing the distance from the fundamental
		frequency to the pitch of the given harmonic in the series.
	 */
	[[nodiscard]] inline CompoundInterval getIntervalOfHarmonic (size_t degree) const noexcept
	{
		return CompoundInterval::fromPitches (fundamental, getHarmonic (degree));
	}

	/** Returns true if these two OvertoneSeries objects have the same fundamental. */
	bool operator==(const OvertoneSeries& other) const noexcept
	{
		return fundamental == other.fundamental;
	}

	/** Returns true if these two OvertoneSeries objects do not have the same fundamental. */
	bool operator!=(const OvertoneSeries& other) const noexcept
	{
		return fundamental != other.fundamental;
	}

private:
	Pitch fundamental;
};

}  // namespace limes::harmony
