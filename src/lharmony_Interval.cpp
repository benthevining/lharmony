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

#include <sstream>
#include <stdexcept>
#include <cmath>
#include "lharmony/lharmony_Interval.h"
#include "lharmony/lharmony_Pitch.h"
#include "lharmony/lharmony_PitchUtils.h"
#include "lharmony/lharmony_Interval_impl.h"

namespace limes::harmony
{

Interval::Interval (int kindToUse, Quality qualityToUse)
	: quality (qualityToUse), kind (kindToUse % 9)
{
	if (! (kind >= 0 && kind <= 8 && kind != 1))
	{
		std::stringstream str;
		str << "Interval - invalid kind " << kind;
		throw std::runtime_error { str.str() };
	}

	if (! isValidQualityForKind (quality, kind))
	{
		std::stringstream str;
		str << "Interval: invalid quality " << qualityToString (quality) << " for kind " << kind;
		throw std::runtime_error { str.str() };
	}
}

Interval::Interval() noexcept
: Interval (0, Quality::Perfect)
{
}

bool Interval::intervalIsPerfectKind() const noexcept
{
	return kind == 0 || kind == 4 || kind == 5 || kind == 8;
}

bool Interval::operator== (const Interval& other) const noexcept
{
	return kind == other.kind && quality == other.quality;
}

bool Interval::operator!= (const Interval& other) const noexcept
{
	return ! (*this == other);
}

Interval& Interval::operator++() noexcept
{
	if (kind == 8 && quality == Quality::Augmented)
		return *this;

	auto incrementKind = [this]
	{
		const auto wasFourth = kind == 4;

		++kind;

		if (kind == 1)
			kind = 2;

		if (intervalIsPerfectKind())
		{
			if (wasFourth)
				quality = Quality::Perfect;
			else
				quality = Quality::Augmented;
		}
		else
		{
			quality = Quality::Major;
		}
	};

	if (intervalIsPerfectKind())
	{
		switch (quality)
		{
			case (Quality::Perfect) :
			{
				quality = Quality::Augmented;
				return *this;
			}
			case (Quality::Augmented) :
			{
				incrementKind();
				return *this;
			}
			case (Quality::Diminished) :
			{
				quality = Quality::Perfect;
				return *this;
			}
		}
	}

	switch (quality)
	{
		case (Quality::Major) :
		{
			quality = Quality::Augmented;
			return *this;
		}
		case (Quality::Minor) :
		{
			quality = Quality::Major;
			return *this;
		}
		case (Quality::Augmented) :
		{
			incrementKind();
			return *this;
		}
		case (Quality::Diminished) :
		{
			quality = Quality::Minor;
			return *this;
		}
	}
}

Interval& Interval::operator--() noexcept
{
	if (kind == 0 && quality == Quality::Perfect)
		return *this;

	if (kind == 2 && quality == Quality::Diminished)
	{
		kind	= 0;
		quality = Quality::Perfect;
		return *this;
	}

	auto decrementKind = [this]
	{
		const auto wasFifth = kind == 5;

		--kind;

		if (kind == 1)
			kind = 0;

		if (intervalIsPerfectKind())
		{
			if (wasFifth)
				quality = Quality::Perfect;
			else
				quality = Quality::Diminished;
		}
		else
		{
			quality = Quality::Minor;
		}
	};

	if (intervalIsPerfectKind())
	{
		switch (quality)
		{
			case (Quality::Perfect) :
			{
				quality = Quality::Diminished;
				return *this;
			}
			case (Quality::Augmented) :
			{
				quality = Quality::Perfect;
				return *this;
			}
			case (Quality::Diminished) :
			{
				decrementKind();
				return *this;
			}
		}
	}

	switch (quality)
	{
		case (Quality::Major) :
		{
			quality = Quality::Minor;
			return *this;
		}
		case (Quality::Minor) :
		{
			quality = Quality::Diminished;
			return *this;
		}
		case (Quality::Augmented) :
		{
			quality = Quality::Major;
			return *this;
		}
		case (Quality::Diminished) :
		{
			decrementKind();
			return *this;
		}
	}
}

Interval Interval::fromNumSemitones (int semitones) noexcept
{
	if (semitones == 13 || semitones == -13)
		return Interval { 8, Quality::Augmented };

	switch (std::abs (semitones) % (semitonesInOctave + 1))
	{
		case (0) : return Interval { 0, Quality::Perfect };
		case (1) : return Interval { 2, Quality::Minor };
		case (2) : return Interval { 2, Quality::Major };
		case (3) : return Interval { 3, Quality::Minor };
		case (4) : return Interval { 3, Quality::Major };
		case (5) : return Interval { 4, Quality::Perfect };
		case (6) : return Interval { 4, Quality::Augmented };
		case (7) : return Interval { 5, Quality::Perfect };
		case (8) : return Interval { 6, Quality::Minor };
		case (9) : return Interval { 6, Quality::Major };
		case (10) : return Interval { 7, Quality::Minor };
		case (11) : return Interval { 7, Quality::Major };
		case (12) : return Interval { 8, Quality::Perfect };
	}
}

Interval Interval::fromPitches (Pitch pitch1, Pitch pitch2) noexcept
{
	return fromNumSemitones (pitch1.getRoundedMidiPitch() - pitch2.getRoundedMidiPitch());
}

Interval Interval::fromPitches (int midiPitch1, int midiPitch2) noexcept
{
	return fromNumSemitones (midiPitch1 - midiPitch2);
}

Interval Interval::operator+ (const Interval& other) const noexcept
{
	return fromNumSemitones (getNumSemitones() + other.getNumSemitones());
}

Interval Interval::operator- (const Interval& other) const noexcept
{
	return fromNumSemitones (getNumSemitones() - other.getNumSemitones());
}

Interval Interval::operator+ (int semitonesToAdd) const noexcept
{
	return fromNumSemitones (getNumSemitones() + semitonesToAdd);
}

Interval Interval::operator- (int semitonesToSubtract) const noexcept
{
	return fromNumSemitones (getNumSemitones() - semitonesToSubtract);
}

Interval& Interval::operator+= (const Interval& other) noexcept
{
	*this = *this + other;
	return *this;
}

Interval& Interval::operator+= (int semitonesToAdd) noexcept
{
	*this = *this + semitonesToAdd;
	return *this;
}

Interval& Interval::operator-= (const Interval& other) noexcept
{
	*this = *this - other;
	return *this;
}

Interval& Interval::operator-= (int semitonesToSubtract) noexcept
{
	*this = *this - semitonesToSubtract;
	return *this;
}

bool Interval::operator> (const Interval& other) const noexcept
{
	if (getNumSemitones() > other.getNumSemitones())
		return true;

	return kind > other.kind;
}

bool Interval::operator<(const Interval& other) const noexcept
{
	if (getNumSemitones() < other.getNumSemitones())
		return true;

	return kind < other.kind;
}

Interval::Quality Interval::getQuality() const noexcept
{
	return quality;
}

int Interval::getKind() const noexcept
{
	return kind;
}

bool Interval::isEnharmonicTo (const Interval& other) const noexcept
{
	return getNumSemitones() == other.getNumSemitones();
}

int Interval::getCents_EqualTemperament() const noexcept
{
	constexpr auto centsPerSemitone = 100;

	return getNumSemitones() * centsPerSemitone;
}

Pitch Interval::applyToPitch (Pitch other, bool above) const noexcept
{
	const auto semitones = getNumSemitones();
	const auto starting	 = other.getRoundedMidiPitch();

	if (above)
		return Pitch { starting + semitones };

	return Pitch { starting - semitones };
}

std::string Interval::qualityToString (Quality q, bool useShort)
{
	if (useShort)
	{
		switch (q)
		{
			case (Quality::Diminished) : return "d";
			case (Quality::Minor) : return "m";
			case (Quality::Major) : return "M";
			case (Quality::Augmented) : return "A";
			case (Quality::Perfect) : return "P";
		}
	}

	switch (q)
	{
		case (Quality::Diminished) : return "Diminished";
		case (Quality::Minor) : return "Minor";
		case (Quality::Major) : return "Major";
		case (Quality::Augmented) : return "Augmented";
		case (Quality::Perfect) : return "Perfect";
	}
}

std::string Interval::getStringDescription (bool useShort) const
{
	std::stringstream stream;

	stream << qualityToString (quality, useShort);

	if (useShort)
	{
		stream << kind;
	}
	else
	{
		switch (kind)
		{
			case (0) : stream << "unison"; break;
			case (2) : stream << "second"; break;
			case (3) : stream << "third"; break;
			case (4) : stream << "fourth"; break;
			case (5) : stream << "fifth"; break;
			case (6) : stream << "sixth"; break;
			case (7) : stream << "seventh"; break;
			case (8) : stream << "octave"; break;
		}
	}

	return stream.str();
}

std::ostream& operator<< (std::ostream& os, const Interval& value)
{
	os << value.getStringDescription (false);
	return os;
}

int Interval::getNumSemitones() const noexcept
{
	auto major_or_minor = [q = quality] (int baseSemitones) -> int
	{
		switch (q)
		{
			case (Quality::Major) : return baseSemitones;
			case (Quality::Minor) : return baseSemitones - 1;
			case (Quality::Augmented) : return baseSemitones + 1;
			case (Quality::Diminished) : return baseSemitones - 2;
			default: return 0; // unreachable
		}
	};

	auto perfect = [q = quality] (int baseSemitones) -> int
	{
		switch (q)
		{
			case (Quality::Perfect) : return baseSemitones;
			case (Quality::Augmented) : return baseSemitones + 1;
			case (Quality::Diminished) : return baseSemitones - 1;
			default: return 0; // unreachable
		}
	};

	switch (kind)
	{
		case (0) : return perfect (0);
		case (2) : return major_or_minor (2);
		case (3) : return major_or_minor (4);
		case (4) : return perfect (5);
		case (5) : return perfect (7);
		case (6) : return major_or_minor (9);
		case (7) : return major_or_minor (11);
		case (8) : return perfect (12);
	}
}

std::vector<double> Interval::getCents_JustIntonation() const
{
	switch (getNumSemitones())
	{
		case (0) :
		{
			switch (kind)
			{
				case (0) : return { 0. };
				case (2) : return { 41.1 };
			}
		}
		case (1) :
		{
			switch (kind)
			{
				case (0) : return { 71., 114. };
				case (2) : return { 100. };
			}
		}
		case (2) :
		{
			switch (kind)
			{
				case (2) : return { 182., 204. };
				case (3) : return { 180., 223., 245. };
			}
		}
		case (3) :
		{
			switch (kind)
			{
				case (2) : return { 253., 275., 298., 318. };
				case (3) : return { 294., 298., 316. };
			}
		}
		case (4) :
		{
			switch (kind)
			{
				case (3) : return { 386., 408., 435. };
				case (4) : return { 427., 384. };
			}
		}
		case (5) :
		{
			switch (kind)
			{
				case (3) : return { 457. };
				case (4) : return { 498. };
			}
		}
		case (6) :
		{
			return { 563., 569., 583., 588., 590., 610., 612., 617., 631., 637. };
		}
		case (7) :
		{
			switch (kind)
			{
				case (5) : return { 701.955 };
				case (6) : return { 743. };
			}
		}
		case (8) :
		{
			switch (kind)
			{
				case (5) : return { 773., 816. };
				case (6) : return { 782., 792., 814. };
			}
		}
		case (9) :
		{
			switch (kind)
			{
				case (6) : return { 884., 906., 933. };
				case (7) : return { 882., 925., 947. };
			}
		}
		case (10) :
		{
			switch (kind)
			{
				case (6) : return { 955., 969., 977., 1020. };
				case (7) : return { 996., 1018. };
			}
		}
		case (11) :
		{
			switch (kind)
			{
				case (7) : return { 1067., 1088. };
				case (8) : return { 1086., 1108., 1129. };
			}
		}
		case (12) :
		{
			switch (kind)
			{
				case (7) : return { 1159., 1180. };
				case (8) : return { 1200. };
			}
		}
		case (13) :
		{
			return { 1271. };
		}
	}
}

Interval Interval::getInverse() const noexcept
{
	switch (getNumSemitones())
	{
		case (0) :
		{
			switch (kind)
			{
				case (0) : return Interval { 8, Quality::Perfect };
				case (2) : return Interval { 7, Quality::Augmented };
			}
		}
		case (1) :
		{
			switch (kind)
			{
				case (0) : return Interval { 8, Quality::Diminished };
				case (2) : return Interval { 7, Quality::Major };
			}
		}
		case (2) :
		{
			switch (kind)
			{
				case (2) : return Interval { 7, Quality::Minor };
				case (3) : return Interval { 6, Quality::Augmented };
			}
		}
		case (3) :
		{
			switch (kind)
			{
				case (2) : return Interval { 7, Quality::Diminished };
				case (3) : return Interval { 6, Quality::Major };
			}
		}
		case (4) :
		{
			switch (kind)
			{
				case (3) : return Interval { 6, Quality::Minor };
				case (4) : return Interval { 5, Quality::Augmented };
			}
		}
		case (5) :
		{
			switch (kind)
			{
				case (3) : return Interval { 6, Quality::Diminished };
				case (4) : return Interval { 5, Quality::Perfect };
			}
		}
		case (6) :
		{
			switch (kind)
			{
				case (4) : return Interval { 5, Quality::Diminished };
				case (5) : return Interval { 4, Quality::Augmented };
			}
		}
		case (7) :
		{
			switch (kind)
			{
				case (5) : return Interval { 4, Quality::Perfect };
				case (6) : return Interval { 3, Quality::Augmented };
			}
		}
		case (8) :
		{
			switch (kind)
			{
				case (5) : return Interval { 4, Quality::Diminished };
				case (6) : return Interval { 3, Quality::Major };
			}
		}
		case (9) :
		{
			switch (kind)
			{
				case (6) : return Interval { 3, Quality::Minor };
				case (7) : return Interval { 2, Quality::Augmented };
			}
		}
		case (10) :
		{
			switch (kind)
			{
				case (6) : return Interval { 3, Quality::Diminished };
				case (7) : return Interval { 2, Quality::Major };
			}
		}
		case (11) :
		{
			switch (kind)
			{
				case (7) : return Interval { 2, Quality::Minor };
				case (8) : return Interval { 0, Quality::Augmented };
			}
		}
		case (12) :
		{
			switch (kind)
			{
				case (7) : return Interval { 2, Quality::Diminished };
				case (8) : return Interval { 0, Quality::Perfect };
			}
		}
		case (13) :
		{
			return Interval { 0, Quality::Augmented };
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/

Pitch operator+ (const Pitch& pitch, const Interval& interval) noexcept
{
	return Pitch { pitch.getRoundedMidiPitch() + interval.getNumSemitones() };
}

Pitch operator- (const Pitch& pitch, const Interval& interval) noexcept
{
	return Pitch { pitch.getRoundedMidiPitch() - interval.getNumSemitones() };
}

}  // namespace limes::harmony
