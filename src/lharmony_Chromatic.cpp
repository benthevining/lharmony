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

#include "lharmony/lharmony_Chromatic.h"
#include "lharmony/lharmony_PitchUtils.h"  // for semitonesInOctave
#include "lharmony/lharmony_PitchClass.h"  // for PitchClass

namespace limes::harmony::scales
{

bool Chromatic::operator== (const Chromatic& other) const
{
	return startingPitchClass == other.startingPitchClass;
}

bool Chromatic::operator!= (const Chromatic& other) const
{
	return startingPitchClass != other.startingPitchClass;
}

std::vector<int> Chromatic::getIntervalsAsSemitones() const
{
	std::vector<int> intervals;

	intervals.reserve (semitonesInOctave);

	for (auto i = 0; i < semitonesInOctave; ++i)
		intervals.emplace_back (1);

	return intervals;
}

PitchClass Chromatic::getPitchClassOfRoot() const noexcept
{
	return startingPitchClass;
}

int Chromatic::notesPerOctave() const noexcept
{
	return semitonesInOctave;
}

}  // namespace limes::harmony::scales
