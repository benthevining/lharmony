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
// IWYU pragma: friend lharmony_KeySignature.h

#pragma once

/** @file
	This file contains implementation details for the KeySignature class.

	@see lharmony_KeySignature.h
	@ingroup lharmony_scales
 */

namespace limes::harmony::scales
{

constexpr KeySignature::KeySignature (Type typeToUse, bool isSharps, int rootNote) noexcept
	: KeySignature (typeToUse, isSharps, PitchClass { rootNote })
{
}

constexpr KeySignature::KeySignature (Type typeToUse, bool isSharps, PitchClass pitchClassOfRoot) noexcept
	: isFlat (! isSharps), type (typeToUse)
{
	struct MajorMinorPair final
	{
		int numMajorAccidentals, numMinorAccidentals;  // cppcheck-suppress unusedStructMember
	};

	const auto pair = [root = pitchClassOfRoot.getAsInt(), flat = isFlat]() -> MajorMinorPair
	{
		if (flat)
		{
			switch (root)
			{
				case (0) : return { 0, 3 };
				case (1) : return { 5, -1 };
				case (2) : return { -1, 1 };
				case (3) : return { 3, 6 };
				case (5) : return { 1, 4 };
				case (6) : return { 6, -1 };
				case (7) : return { -1, 2 };
				case (8) : return { 4, 7 };
				case (9) : return { -1, 0 };
				case (10) : return { 2, 5 };
				case (11) : return { 7, -1 };
			}
		}

		switch (root)
		{
			case (0) : return { 0, -1 };
			case (1) : return { 7, 4 };
			case (2) : return { 2, -1 };
			case (3) : return { -1, 6 };
			case (4) : return { 4, 1 };
			case (6) : return { 6, 3 };
			case (7) : return { 1, -1 };
			case (8) : return { -1, 5 };
			case (9) : return { 3, 0 };
			case (10) : return { -1, 7 };
			case (11) : return { 5, 2 };
		}
	}();

	if (type == Type::Major)
		numAccidentals = pair.numMajorAccidentals;
	else
		numAccidentals = pair.numMinorAccidentals;

	// LIMES_ASSERT (numAccidentals >= 0 && numAccidentals <= 7);
}

constexpr KeySignature::KeySignature (Type typeToUse, int rootPitch) noexcept
	: KeySignature (typeToUse, PitchClass { rootPitch })
{
}

constexpr KeySignature::KeySignature (Type typeToUse, PitchClass pitchClassOfRoot) noexcept
	: KeySignature (typeToUse,
					useSharpsForRootByDefault (pitchClassOfRoot, typeToUse),
					pitchClassOfRoot)
{
}

constexpr bool KeySignature::useSharpsForRootByDefault (PitchClass root, Type type) noexcept
{
	const auto r = root.getAsInt();

	if (type == Type::Major)
		return r == 2 || r == 4 || r == 7 || r == 9 || r == 11;

	return r == 1 || r == 4 || r == 6 || r == 8 || r == 11;
}

constexpr KeySignature::KeySignature() noexcept
	: KeySignature (0, false, Type::Major)
{
}

constexpr KeySignature::KeySignature (int numSharpsOrFlats, bool isSharps, Type typeToUse) noexcept
	: numAccidentals (numSharpsOrFlats), isFlat (! isSharps), type (typeToUse)
{
	// LIMES_ASSERT (numAccidentals >= 0 && numAccidentals <= 7);
}

constexpr bool KeySignature::isRelativeKeyOf (const KeySignature& other) const noexcept
{
	return hasOppositeTonality (other) && numAccidentals == other.numAccidentals && isFlat == other.isFlat;
}

constexpr bool KeySignature::hasOppositeTonality (const KeySignature& other) const noexcept
{
	if (type == Type::Major)
		return other.type != Type::Major;

	return other.type == Type::Major;
}

constexpr bool KeySignature::rootHasEnharmonicKey (int root, Type type) noexcept
{
	if (type == Type::Major)
		return root == 11 || root == 8 || root == 6 || root == 3 || root == 1;

	return root == 3 || root == 8 || root == 10;
}

constexpr bool KeySignature::operator== (const KeySignature& other) const noexcept
{
	return numAccidentals == other.numAccidentals && isFlat == other.isFlat && type == other.type;
}

constexpr bool KeySignature::operator!= (const KeySignature& other) const noexcept
{
	return ! (*this == other);
}

constexpr bool KeySignature::isFlatKey() const noexcept
{
	if (numAccidentals == 0)
		return false;

	return isFlat;
}

constexpr bool KeySignature::isSharpKey() const noexcept
{
	if (numAccidentals == 0)
		return false;

	return ! isFlat;
}

constexpr bool KeySignature::isMajorKey() const noexcept
{
	return type == Type::Major;
}

constexpr bool KeySignature::isMinorKey() const noexcept
{
	return ! isMajorKey();
}

constexpr int KeySignature::getNumSharps() const noexcept
{
	if (isFlat)
		return 0;

	return numAccidentals;
}

constexpr int KeySignature::getNumFlats() const noexcept
{
	if (! isFlat)
		return 0;

	return numAccidentals;
}

constexpr KeySignature::Type KeySignature::getKeyType() const noexcept
{
	return type;
}

}  // namespace limes::harmony::scales
