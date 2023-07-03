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

#include <cmath>
#include <sstream>
#include <stdexcept>
#include "lharmony/lharmony_Pitch.h"
#include "lharmony/lharmony_PitchUtils.h"
#include "lharmony/lharmony_Interval.h"
#include "lharmony/lharmony_CompoundInterval.h"
#include "lharmony/lharmony_IntervalConstants.h"

namespace limes::harmony
{

CompoundInterval::CompoundInterval (int octaves, const Interval& simpleInterval) noexcept
	: interval (simpleInterval), numOctaves (octaves)
{
	constexpr auto octave_kind = 8;

	if (interval.getKind() == octave_kind)
	{
		const auto quality_ = interval.getQuality();

		if (quality_ != Interval::Quality::Diminished)
		{
			++numOctaves;
			interval = Interval { 0, quality_ };
		}
	}
}

CompoundInterval::CompoundInterval (int kindToUse, Interval::Quality qualityToUse)
{
	if (! Interval::isValidQualityForKind (qualityToUse, kindToUse))
	{
		std::stringstream str;
		str << "Cannot construct CompoundInterval - quality " << Interval::qualityToString (qualityToUse) << " is invalid for kind " << kindToUse;
		throw std::runtime_error { str.str() };
	}

	if (kindToUse <= 8)
	{
		numOctaves = 0;
		interval   = Interval { kindToUse, qualityToUse };
		return;
	}

	numOctaves = (kindToUse - 1) / 7;

	const auto intervalKind = kindToUse - (7 * numOctaves);

	if (intervalKind <= 0)
		interval = Interval();
	else
		interval = Interval { intervalKind, qualityToUse };
}

CompoundInterval::CompoundInterval (int numSemitones) noexcept
{
	numOctaves = numSemitones / semitonesInOctave;
	interval   = Interval::fromNumSemitones (numSemitones - (numOctaves * 12));
}

CompoundInterval CompoundInterval::fromPitches (int midiPitch1, int midiPitch2) noexcept
{
	return CompoundInterval { std::abs (midiPitch2 - midiPitch1) };
}

bool CompoundInterval::operator== (const Interval& other) const noexcept
{
	if (other == intervals::perfect::octave)
		return numOctaves == 1 && interval == intervals::perfect::unison;

	return getSimpleInterval() == other && getNumSemitones() == other.getNumSemitones();
}

bool CompoundInterval::operator!= (const Interval& other) const noexcept
{
	return ! (*this == other);
}

bool CompoundInterval::operator> (const Interval& other) const noexcept
{
	return getSimpleInterval() > other || getNumSemitones() > other.getNumSemitones();
}

bool CompoundInterval::operator<(const Interval& other) const noexcept
{
	return getSimpleInterval() < other || getNumSemitones() < other.getNumSemitones();
}

Interval CompoundInterval::getSimpleInterval() const noexcept
{
	return interval;
}

std::vector<double> CompoundInterval::getCents_JustIntonation() const
{
	const auto octaveCents = static_cast<double> (numOctaves) * 1200.;

	auto array = interval.getCents_JustIntonation();

	for (auto i = 0; i < static_cast<int> (array.size()); ++i)
		array[static_cast<std::vector<double>::size_type> (i)] += octaveCents;

	return array;
}

CompoundInterval CompoundInterval::fromPitches (const Pitch& pitch1, const Pitch& pitch2) noexcept
{
	return CompoundInterval { std::abs (pitch2.getRoundedMidiPitch() - pitch1.getRoundedMidiPitch()) };
}

int CompoundInterval::getKind() const noexcept
{
	const auto simple = [kind = interval.getKind()]
	{
		if (kind > 0)
			return kind - 1;

		return kind;
	}();

	return (numOctaves * 7) + simple + 1;
}

Interval::Quality CompoundInterval::getQuality() const noexcept
{
	return interval.getQuality();
}

int CompoundInterval::getNumSemitones() const noexcept
{
	return interval.getNumSemitones() + (numOctaves * semitonesInOctave);
}

bool CompoundInterval::hasSameSimpleInterval (const CompoundInterval& other) const noexcept
{
	return interval == other.interval;
}

}  // namespace limes::harmony
