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

#include "lharmony/lharmony_KeySignature.h"
#include "lharmony/lharmony_PitchClass.h"

namespace limes::harmony::scales
{

std::vector<int> KeySignature::getIntervalsAsSemitones() const
{
	switch (type)
	{
		case (Type::Major) : return { 2, 2, 1, 2, 2, 2, 1 };
		case (Type::NaturalMinor) : return { 2, 1, 2, 2, 1, 2, 2 };
		case (Type::HarmonicMinor) : return { 2, 1, 2, 2, 1, 3, 1 };
	}
}

PitchClass KeySignature::getPitchClassOfRoot() const noexcept
{
	struct MajorMinorPair final
	{
		int majorRoot, minorRoot; // cppcheck-suppress unusedStructMember
	};

	const auto pair = [num = numAccidentals, flat = isFlat]() -> MajorMinorPair
	{
		if (flat)
		{
			switch (num)
			{
				case (0) : return { 0, 9 };
				case (1) : return { 5, 2 };
				case (2) : return { 10, 7 };
				case (3) : return { 3, 0 };
				case (4) : return { 8, 5 };
				case (5) : return { 1, 10 };
				case (6) : return { 6, 3 };
				case (7) : return { 11, 8 };
			}
		}

		switch (num)
		{
			case (0) : return { 0, 9 };
			case (1) : return { 7, 4 };
			case (2) : return { 2, 11 };
			case (3) : return { 9, 6 };
			case (4) : return { 4, 1 };
			case (5) : return { 11, 8 };
			case (6) : return { 6, 3 };
			case (7) : return { 1, 10 };
		}
	}();

	const auto pitchClassInt = [&pair, t = type]
	{
		if (t == Type::Major)
			return pair.majorRoot;

		return pair.minorRoot;
	}();

	return PitchClass { pitchClassInt };
}

int KeySignature::notesPerOctave() const noexcept
{
	return 8;
}

bool KeySignature::hasEnharmonicKey() const noexcept
{
	return rootHasEnharmonicKey (getPitchClassOfRoot(), type);
}

KeySignature KeySignature::getEnharmonicKey() const noexcept
{
	const auto root = getPitchClassOfRoot();

	if (! rootHasEnharmonicKey (root, type))
		return { *this };

	return KeySignature { type, isFlat, root };
}

bool KeySignature::isEnharmonicKeyOf (const KeySignature& other) const noexcept
{
	return type == other.type && isFlat != other.isFlat && getPitchClassOfRoot() == other.getPitchClassOfRoot();
}

KeySignature KeySignature::getRelativeKey() const noexcept
{
	const auto otherType = [t = type]
	{
		if (t == Type::Major)
			return Type::NaturalMinor;

		return Type::Major;
	}();

	return KeySignature { numAccidentals, ! isFlat, otherType };
}

KeySignature KeySignature::getParallelKey() const noexcept
{
	const auto parallelType = type == Type::Major ? Type::NaturalMinor : Type::Major;

	const auto root = getPitchClassOfRoot();

	// automatically detect whether to use flats or sharps for the parallel key
	auto key = KeySignature { parallelType, root };

	// see if we got the spelling wrong
	if (key.hasEnharmonicKey() && key.isFlat != isFlat)
		return KeySignature { parallelType, key.isFlat, root };

	return key;
}

bool KeySignature::isParallelKeyOf (const KeySignature& other) const noexcept
{
	return hasOppositeTonality (other) && getPitchClassOfRoot() == other.getPitchClassOfRoot();
}

KeySignature KeySignature::getDominantKey() const noexcept
{
	const PitchClass dominant { getPitchClassOfRoot() + 7 };

	return KeySignature { Type::Major, dominant };
}

bool KeySignature::isDominantKeyOf (const KeySignature& other) const noexcept
{
	if (type != Type::Major)
		return false;

	const PitchClass dominant { other.getPitchClassOfRoot() + 7 };

	return getPitchClassOfRoot() == dominant;
}

KeySignature KeySignature::withType (Type newType) const noexcept
{
	if (newType == type)
		return *this;

	if (isMinorKey() && (newType == Type::NaturalMinor || newType == Type::HarmonicMinor))
		return KeySignature { numAccidentals, ! isFlat, newType };

	return KeySignature { newType, getPitchClassOfRoot() };
}

}  // namespace limes::harmony::scales
