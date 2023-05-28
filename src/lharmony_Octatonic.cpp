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

#include "lharmony/lharmony_Octatonic.h"
#include "lharmony/lharmony_PitchClass.h"

namespace limes::harmony::scales
{

bool Octatonic::operator== (const Octatonic& other) const
{
	return startWithHalfStep == other.startWithHalfStep && pitchClassOfRoot == other.pitchClassOfRoot;
}

bool Octatonic::operator!= (const Octatonic& other) const
{
	return ! (*this == other);
}

std::vector<int> Octatonic::getIntervalsAsSemitones() const
{
	std::vector<int> intervals;

	auto semitone = startWithHalfStep;

	for (auto i = 0; i < 8; ++i)
	{
		if (semitone)
			intervals.emplace_back (1);
		else
			intervals.emplace_back (2);

		semitone = ! semitone;
	}

	return intervals;
}

PitchClass Octatonic::getPitchClassOfRoot() const noexcept
{
	return pitchClassOfRoot;
}

int Octatonic::notesPerOctave() const noexcept
{
	return 8;
}

}  // namespace limes::harmony::scales
