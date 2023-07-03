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

// IWYU pragma: private
// IWYU pragma: friend lharmony_CompoundInterval.h

#pragma once

/** @file
	This file contains implementation details for the \c CompoundInterval class.

	@see lharmony_CompoundInterval.h
	@ingroup lharmony_intervals
 */

namespace limes::harmony
{

constexpr bool CompoundInterval::operator== (const CompoundInterval& other) const noexcept
{
	return numOctaves == other.numOctaves && interval == other.interval;
}

constexpr bool CompoundInterval::operator!= (const CompoundInterval& other) const noexcept
{
	return ! (*this == other);
}

constexpr bool CompoundInterval::operator> (const CompoundInterval& other) const noexcept
{
	if (numOctaves < other.numOctaves)
		return false;

	return interval > other.interval;
}

constexpr bool CompoundInterval::operator<(const CompoundInterval& other) const noexcept
{
	if (numOctaves > other.numOctaves)
		return false;

	return interval < other.interval;
}

constexpr int CompoundInterval::getNumOctaves() const noexcept
{
	return numOctaves;
}

}  // namespace limes::harmony
