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
#include "lharmony/lharmony_KeySignature.h"		 
#include "lharmony/lharmony_Scale.h"			
#include "lharmony/lharmony_PitchClass.h"  

/** @file
	This file defines the Mode %scale class.

	@ingroup lharmony_scales
 */

namespace limes::harmony::scales
{

/** This class represents a church %mode %scale.

	Here is a table of all modes:

	Name       | Example with no sharps/flats | Example starting on C  | Interval pattern
	---------- | ---------------------------- | ---------------------- | -----------------
	Ionian     | C D E F G A B C              | C D  E  F  G  A  B  C  | W W H W W W H
	Dorian     | D E F G A B C D              | C D  Eb F  G  A  Bb C  | W H W W W H W
	Phrygian   | E F G A B C D E              | C Db Eb F  G  Ab Bb C  | H W W W H W W
	Lydian     | F G A B C D E F              | C D  E  F# G  A  B  C  | W W W H W W H
	Mixolydian | G A B C D E F G              | C D  E  F  G  A  Bb C  | W W H W W H W
	Aeolian    | A B C D E F G A              | C D  Eb F  G  Ab Bb C  | W H W W H W W
	Locrian    | B C D E F G A B              | C Dd Eb F  Gb Ab Bb C  | H W W H W W W

	@ingroup lharmony_scales

	@todo Provide Mode objects as constants
 */
class LHARM_EXPORT Mode final : public Scale
{
public:
	/** Represents which kind of %mode this %scale is. */
	enum class Type
	{
		Ionian,		 ///< The Ionian mode.
		Dorian,		 ///< The Dorian mode.
		Phrygian,	 ///< The Phrygian mode.
		Lydian,		 ///< The Lydian mode.
		Mixolydian,	 ///< The Mixolydian mode.
		Aeolian,	 ///< The Aeolian mode.
		Locrian		 ///< The Locrian mode.
	};

	/** @name Constructors */
	///@{

	/** Creates a modal %scale object with the given type and root. */
	constexpr Mode (Type typeToUse, PitchClass pitchClassOfRoot) noexcept
		: type (typeToUse), rootPitchClass (pitchClassOfRoot)
	{
	}

	/** Creates a modal %scale of the given type, starting on the given MIDI note. */
	constexpr Mode (Type typeToUse, int rootNote) noexcept
		: type (typeToUse), rootPitchClass (rootNote)
	{
	}

	///@}

	Mode (const Mode&) = default;
	Mode& operator=(const Mode&) = default;

	Mode (Mode&&) = default;
	Mode& operator=(Mode&&) = default;

	/** Returns true if the other modal %scale has the same type and root as this one. */
	[[nodiscard]] constexpr bool operator== (const Mode& other) const noexcept
	{
		return type == other.type && rootPitchClass == other.rootPitchClass;
	}

	/** Returns true if the other modal %scale does not have the same type and root as this one. */
	[[nodiscard]] constexpr bool operator!= (const Mode& other) const noexcept
	{
		return ! (*this == other);
	}

	[[nodiscard]] constexpr Type getType() const noexcept
	{
		return type;
	}

	/** Returns the set of intervals that make up this %mode. */
	[[nodiscard]] std::vector<int> getIntervalsAsSemitones() const final;

	/** Returns the %pitch class of the root of this %mode. */
	[[nodiscard]] PitchClass getPitchClassOfRoot() const noexcept final;

	/** Returns 8. */
	[[nodiscard]] int notesPerOctave() const noexcept final;

	/** Returns the number of sharps that make up the key signature for this %mode. */
	[[nodiscard]] int getNumSharps() const noexcept;

	/** Returns the number of flats that make up the key signature for this %mode. */
	[[nodiscard]] int getNumFlats() const noexcept;

	/** Returns an equivalent key signature for this mode. The returned key signature contains all the same %pitch classes as this %mode, but may have a different root. */
	[[nodiscard]] KeySignature getKeySignature() const noexcept;

private:
	Type type { Type::Ionian };

	PitchClass rootPitchClass { 0 };
};

}  // namespace limes::harmony::scales
