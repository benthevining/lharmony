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
#include <string>
#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_Pitch.h"

/** @defgroup lharmony_intervals Intervals
	Utilities for working with musical pitch intervals.

	@ingroup limes_harmony
 */

/** @file
	This file defines the \c Interval class.

	@ingroup lharmony_intervals
 */

namespace limes::harmony
{

/** A class that represents a musical interval between two pitches.

	This class is meant for intervals that are an octave or smaller, and that can be expressed as a whole number of semitones.
	(Technically, the largest interval representable by this class is an augmented octave.)
	To represent intervals larger than an octave, use the CompoundInterval class.

	An interval is represented as a kind (unison, second, third, etc) and a quality (major, minor, perfect, augmented, or diminished).
	Note that not every quality is valid for every kind -- a "perfect third" or a "major fifth" do not exist.

	Here is a table of all valid kind/quality combinations:

	Kind as integer | Name    | Valid qualities
	--------------- | ------- | ------------------------------------
	0               | Unison  | Perfect, augmented
	2               | Second  | Diminished, minor, major, augmented
	3               | Third   | Diminished, minor, major, augmented
	4               | Fourth  | Diminished, perfect, augmented
	5               | Fifth   | Diminished, perfect, augmented
	6               | Sixth   | Diminished, minor, major, augmented
	7               | Seventh | Diminished, minor, major, augmented
	8               | Octave  | Diminished, perfect, augmented

	And here is a listing of all possible intervals that this class can represent:

	Name(s)                            | Semitones
	---------------------------------- | ----------
	Perfect unison, diminished second  | 0
	Minor second, augmented unison     | 1
	Major second, diminished third     | 2
	Minor third, augmented second      | 3
	Major third, diminished fourth     | 4
	Perfect fourth, augmented third    | 5
	Diminished fifth, augmented fourth | 6
	Perfect fifth, diminished sixth    | 7
	Minor sixth, augmented fifth       | 8
	Major sixth, diminished seventh    | 9
	Minor seventh, augmented sixth     | 10
	Major seventh, diminished octave   | 11
	Perfect octave, augmented seventh  | 12
	Augmented octave                   | 13

	Some convenient predefined interval objects can be found in the \c intervals namespace.

	@ingroup lharmony_intervals
	@see CompoundInterval, MicrotonalInterval, isValidQualityForKind()

	@todo throw exception in constructor if necessary
	@todo support for doubly augmented/diminished intervals?

	@todo I feel like MicrotonalInterval should have the same base class. Perhaps the Interval
	base class should have a smaller interface, and this class actually becomes DiatonicInterval
 */
class LHARM_EXPORT Interval
{
public:
	/** Destructor. */
	virtual ~Interval() = default;

	Interval (const Interval&)			  = default;
	Interval& operator= (const Interval&) = default;

	Interval (Interval&&)			 = default;
	Interval& operator= (Interval&&) = default;

	/** Describes the quality of the %interval.
		Note that not all possible quality values are valid for every possible %interval type; a "major fifth" or a "perfect third" do not exist.
		@see isValidQualityForKind(), getQuality()
	 */
	enum class Quality
	{
		Diminished,	 ///< A diminished interval.
		Minor,		 ///< A minor interval.
		Major,		 ///< A major interval.
		Augmented,	 ///< An augmented interval.
		Perfect		 ///< A perfect interval.
	};

	/** Returns a string description of the specified interval quality. */
	[[nodiscard]] static std::string qualityToString (Quality q, bool useShort = false);

	/** @name Constructors */
	///@{

	/** Creates an %interval representing a perfect unison. */
	Interval() noexcept;

	/** Creates an %interval with a specified kind and quality.
		If the kind or quality parameters are invalid, an assertion will be thrown.
		@param kindToUse The kind of %interval to create -- 0 for unison, 2 for second, 3 for third, etc. Note that 1 is not a valid value, and values greater than 8 will be reduced to their equivalent intervals that are within one octave (ie, using the modulus operator).
		@param qualityToUse The quality of %interval to create. Note that not all possible quality values are valid for every possible %interval type; a "major fifth" or a "perfect third" do not exist.
		@see isValidQualityForKind()
	 */
	Interval (int kindToUse, Quality qualityToUse);

	///@}

	/** @name Creation functions */
	///@{

	/** Creates an %interval from a number of semitones.
		This uses reasonable defaults, always preferring major, minor, or perfect intervals when available instead of augmented or diminished.
		@see fromPitches
	 */
	[[nodiscard]] static Interval fromNumSemitones (int semitones) noexcept;

	/** Creates an %interval from the distance between two pitch objects.
		This uses reasonable defaults, always preferring major, minor, or perfect intervals when available instead of augmented or diminished.
		@see fromNumSemitones
	 */
	[[nodiscard]] static Interval fromPitches (Pitch pitch1, Pitch pitch2) noexcept;

	/** Creates an %interval from the distance between two MIDI pitches.
		This uses reasonable defaults, always preferring major, minor, or perfect intervals when available instead of augmented or diminished.
		@see fromNumSemitones
	 */
	[[nodiscard]] static Interval fromPitches (int midiPitch1, int midiPitch2) noexcept;

	///@}

	/** @name Equality comparisons */
	///@{

	/** Returns true if the two intervals are exactly equal -- that is, have the same kind and quality.
		Note that this will return false for intervals that represent the same number of semitones but are spelled differently.
		@see isEnharmonicTo()
	 */
	[[nodiscard]] bool operator== (const Interval& other) const noexcept;

	/** Returns true if the two intervals are not exactly equal.
		Note that this will return true for intervals that represent the same number of semitones but are spelled differently.
		@see isEnharmonicTo()
	 */
	[[nodiscard]] bool operator!= (const Interval& other) const noexcept;

	/** Returns true if the two intervals represent the same number of semitones, regardless of their enharmonic spelling.
		For example, a diminished fifth is enharmonic to an augmented fourth.
	 */
	[[nodiscard]] bool isEnharmonicTo (const Interval& other) const noexcept;

	///@}

	/** Returns true if this %interval is semantically larger than the other one, taking enharmonic spellings into account.
		For example, this will tell you that a diminished fifth is "larger" than an augmented fourth.
	 */
	[[nodiscard]] bool operator> (const Interval& other) const noexcept;

	/** Returns true if this %interval is semantically smaller than the other one, taking enharmonic spellings into account.
		For example, this will tell you that an augmented fourth is "smaller" than a diminished fifth.
	 */
	[[nodiscard]] bool operator<(const Interval& other) const noexcept;

	/** @name Addition */
	///@{

	/** Adds another %interval object to this one. */
	[[nodiscard]] Interval operator+ (const Interval& other) const noexcept;

	/** Adds a number of semitones to this %interval. */
	[[nodiscard]] Interval operator+ (int semitonesToAdd) const noexcept;

	/** Adds another %interval object to this one. */
	Interval& operator+= (const Interval& other) noexcept;

	/** Adds a number of semitones to this %interval. */
	Interval& operator+= (int semitonesToAdd) noexcept;

	/** Increments this %interval by one semitone, preserving the kind by manipulating the quality where possible.
		For example, a major second will increment to an augmented second, rather than a minor third.
		A perfect octave will increment to an augmented octave.
		Calling the increment operator on an augmented octave will do nothing.
	 */
	Interval& operator++() noexcept;

	///@}

	/** @name Subtraction */
	///@{

	/** Subtracts another %interval object from this one. */
	[[nodiscard]] Interval operator- (const Interval& other) const noexcept;

	/** Subtracts a number of semitones from this %interval. */
	[[nodiscard]] Interval operator- (int semitonesToSubtract) const noexcept;

	/** Subtracts another %interval object from this one. */
	Interval& operator-= (const Interval& other) noexcept;

	/** Subtracts a number of semitones from this %interval. */
	Interval& operator-= (int semitonesToSubtract) noexcept;

	/** Decrements this %interval by one semitone, preserving the kind by manipulating the quality where possible.
		For example, a minor second will decrement to a diminished second, rather than a perfect unison.
		In the special case of a diminished second, it will decrement to a perfect unison (even though these two intervals are enharmonically equivalent).
		Calling the decrement operator on a perfect unison will do nothing.
	 */
	Interval& operator--() noexcept;

	///@}

	/** Returns the %interval that is the inverse of this one, taking enharmonic spellings into account.
		An %interval and its inverse add together to form a perfect octave -- for example, a major second's inverse is a minor seventh, a perfect fourth's inverse is a perfect fifth, etc.
	 */
	[[nodiscard]] Interval getInverse() const noexcept;

	/** Returns the number of semitones that this %interval represents.
		@see getKind()
	 */
	[[nodiscard]] virtual int getNumSemitones() const noexcept;

	/** Returns the kind of this %interval as an integer.
		0 represents unison, 2 is a second, 3 is a third, etc.
		Note that this will never return 1.
		@see getNumSemitones()
	 */
	[[nodiscard]] virtual int getKind() const noexcept;

	/** Returns the quality of this %interval. */
	[[nodiscard]] virtual Quality getQuality() const noexcept;

	/** @name Cents measurements */
	///@{

	/** Returns an array of possible cents values this %interval can represent in just intonation, taking enharmonic spelling into account.
		@see getJustRatios, getCents_EqualTemperament
	 */
	[[nodiscard]] virtual std::vector<double> getCents_JustIntonation() const;

	/** Returns the number of cents this %interval represents in equal temperament.
		Note that, unlike just intonation, enharmonic spellings represent equal numbers of cents in equal temperament.
		@see getCents_JustIntonation
	 */
	[[nodiscard]] int getCents_EqualTemperament() const noexcept;

	///@}

	/** Returns a new pitch object that represents the note this interval's distance above or below the passed pitch object.
		@param other The pitch object to start from.
		@param above When true, the returned pitch will be this interval's distance above the passed pitch. When false, the returned pitch will be this interval's distance below the passed pitch.
	 */
	[[nodiscard]] Pitch applyToPitch (Pitch other, bool above) const noexcept;

	/** Returns a string description of this interval, such as "major second". If the \c useShort
		parameter is true, then an abbreviated string will be returned, such as "M2".
	 */
	[[nodiscard]] std::string getStringDescription (bool useShort = false) const;

	/** Returns true if the quality is valid for the given kind of %interval.
		For example, a perfect fourth or fifth is valid, while a perfect third or perfect second is not. A major or minor third is valid, while a major fourth or minor fifth is not.
		Note the special case that a diminished unison is invalid; unisons can only be perfect or augmented.
		Note that a kind of 1 is invalid.

		Here is a table of all valid kind/quality combinations:

		Kind as integer | Name    | Valid qualities
		--------------- | ------- | ------------------------------------
		0               | Unison  | Perfect, augmented
		2               | Second  | Diminished, minor, major, augmented
		3               | Third   | Diminished, minor, major, augmented
		4               | Fourth  | Diminished, perfect, augmented
		5               | Fifth   | Diminished, perfect, augmented
		6               | Sixth   | Diminished, minor, major, augmented
		7               | Seventh | Diminished, minor, major, augmented
		8               | Octave  | Diminished, perfect, augmented
	 */
	[[nodiscard]] static constexpr bool isValidQualityForKind (Quality quality, int kind) noexcept;

private:
	[[nodiscard]] bool intervalIsPerfectKind() const noexcept;

	Quality quality { Quality::Major };

	int kind { 0 };
};

constexpr bool Interval::isValidQualityForKind (Quality quality, int kind) noexcept
{
	if (kind == 1)
		return false;

	const auto baseKind = [k = kind]  // NOLINT
	{
		const auto base = k % 8;

		if (k > 8)
			return base + (k / 8);

		return base;
	}();

	if (baseKind == 0 || baseKind == 4 || baseKind == 5)
	{
		const auto base = quality != Quality::Major && quality != Quality::Minor;

		if (kind == 0)
			return base && quality != Quality::Diminished;

		return base;
	}

	return quality != Quality::Perfect;
}


/** Adds an interval to the given pitch and returns a new pitch object at the resulting pitch.
	@ingroup music_intervals
 */
LHARM_EXPORT Pitch operator+ (const Pitch& pitch, const Interval& interval) noexcept;

/** Subtracts an interval from the given pitch and returns a new pitch object at the resulting pitch.
	@ingroup music_intervals
 */
LHARM_EXPORT Pitch operator- (const Pitch& pitch, const Interval& interval) noexcept;

/** Writes a string description of the Interval to the output stream.

	@ingroup music_intervals
	@relates Interval
	@see Interval::getStringDescription()
 */
LHARM_EXPORT std::ostream& operator<< (std::ostream& os, const Interval& value);

}  // namespace limes::harmony
