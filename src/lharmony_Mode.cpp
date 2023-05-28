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

#include <algorithm>
#include "lharmony/lharmony_Mode.h"
#include "lharmony/lharmony_KeySignature.h"		  
#include "lharmony/lharmony_PitchClass.h"  

namespace limes::harmony::scales
{

std::vector<int> Mode::getIntervalsAsSemitones() const
{
	switch (type)
	{
		case (Type::Ionian) : return { 2, 2, 1, 2, 2, 2, 1 };
		case (Type::Dorian) : return { 2, 1, 2, 2, 2, 1, 2 };
		case (Type::Phrygian) : return { 1, 2, 2, 2, 1, 2, 2 };
		case (Type::Lydian) : return { 2, 2, 2, 1, 2, 2, 1 };
		case (Type::Mixolydian) : return { 2, 2, 1, 2, 2, 1, 2 };
		case (Type::Aeolian) : return { 2, 1, 2, 2, 1, 2, 2 };
		case (Type::Locrian) : return { 1, 2, 2, 1, 2, 2, 2 };
	}
}

PitchClass Mode::getPitchClassOfRoot() const noexcept
{
	return rootPitchClass;
}

int Mode::notesPerOctave() const noexcept
{
	return 8;
}

[[nodiscard]] static constexpr int numAddedFlats (Mode::Type t) noexcept
{
	switch (t)
	{
		case (Mode::Type::Ionian) : return 0;
		case (Mode::Type::Dorian) : return 2;
		case (Mode::Type::Phrygian) : return 4;
		case (Mode::Type::Lydian) : return -1;
		case (Mode::Type::Mixolydian) : return 1;
		case (Mode::Type::Aeolian) : return 3;
		case (Mode::Type::Locrian) : return 5;
	}
}

int Mode::getNumSharps() const noexcept
{
	const auto parallelMajor = KeySignature { KeySignature::Type::Major, rootPitchClass };

	const auto numSharps = parallelMajor.isSharpKey() ? parallelMajor.getNumSharps() : -parallelMajor.getNumFlats();

	return std::max (0, numSharps - numAddedFlats (type));
}

int Mode::getNumFlats() const noexcept
{
	const auto parallelMajor = KeySignature { KeySignature::Type::Major, rootPitchClass };

	const auto numFlats = parallelMajor.isFlatKey() ? parallelMajor.getNumFlats() : -parallelMajor.getNumSharps();

	return std::max (0, numFlats + numAddedFlats (type));
}

KeySignature Mode::getKeySignature() const noexcept
{
	if (type == Type::Aeolian)
		return KeySignature { KeySignature::Type::NaturalMinor, rootPitchClass.getAsInt() };

	if (const auto flats = getNumFlats(); flats > 0)
		return KeySignature { flats, false, KeySignature::Type::Major };

	return KeySignature { getNumSharps(), true, KeySignature::Type::Major };
}

}  // namespace limes::harmony::scales
