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

#include "lharmony/lharmony_WholeTone.h"
#include "lharmony/lharmony_PitchClass.h"  // for PitchClass

namespace limes::harmony::scales
{

bool WholeTone::operator== (const WholeTone& other) const
{
	return startingPitchClass == other.startingPitchClass;
}

bool WholeTone::operator!= (const WholeTone& other) const
{
	return startingPitchClass != other.startingPitchClass;
}

std::vector<int> WholeTone::getIntervalsAsSemitones() const
{
	std::vector<int> intervals;

	intervals.reserve (6);

	for (auto i = 0; i < 6; ++i)
		intervals.emplace_back (2);

	return intervals;
}

PitchClass WholeTone::getPitchClassOfRoot() const noexcept
{
	return startingPitchClass;
}

int WholeTone::notesPerOctave() const noexcept
{
	return 6;
}

}  // namespace limes::harmony::scales
