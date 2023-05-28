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
#include "lharmony/lharmony_Scale.h"
#include "lharmony/lharmony_PitchUtils.h"
#include "lharmony/lharmony_Interval.h"
#include "lharmony/lharmony_Pitch.h"			
#include "lharmony/lharmony_PitchClass.h"	

namespace limes::harmony::scales
{

bool Scale::operator== (const Scale& other) const
{
	return getPitchClassOfRoot() == other.getPitchClassOfRoot() && getIntervalsAsSemitones() == other.getIntervalsAsSemitones();
}

bool Scale::operator!= (const Scale& other) const
{
	return ! (*this == other);
}

std::vector<Interval> Scale::getIntervals() const
{
	const auto semitones = getIntervalsAsSemitones();

	std::vector<Interval> intervals;

	std::transform (std::begin (semitones), std::end (semitones), std::begin (intervals), 
					[] (const auto interval) { return Interval::fromNumSemitones (interval); });

	return intervals;
}

bool Scale::containsPitch (Pitch pitch) const
{
	return containsPitchClass (pitch.getPitchClass());
}

bool Scale::containsPitch (int midiNoteNumber) const
{
	return containsPitchClass (PitchClass { midiNoteNumber });
}

bool Scale::containsPitchClass (PitchClass pitchClass) const
{
	const auto pitchClasses = getPitchClasses();

	return std::find (std::begin (pitchClasses), std::end (pitchClasses), pitchClass) != std::end (pitchClasses);
}

std::vector<PitchClass> Scale::getPitchClasses() const
{
	std::vector<PitchClass> pitchClasses;

	auto lastPitchClass = getPitchClassOfRoot();

	pitchClasses.emplace_back (lastPitchClass);

	for (auto semitones : getIntervalsAsSemitones())
	{
		lastPitchClass += semitones;
		pitchClasses.emplace_back (lastPitchClass);
	}

	return pitchClasses;
}

std::vector<Pitch> Scale::getPitches (int octaveNumber) const
{
	const auto startingNote = [this, octaveNumber]
	{
		auto starting = lowestNoteOfMidiOctave (octaveNumber);

		while (! containsPitch (starting))
			++starting;

		return starting;
	}();

	std::vector<Pitch> pitches;

	const auto semitones = getIntervalsAsSemitones();

	std::transform (std::begin (semitones), std::end (semitones), std::begin (pitches), 
					[startingNote] (const auto interval) { return Pitch { startingNote + interval }; });

	return pitches;
}

std::vector<Pitch> Scale::getPitches (int lowestMidiNote, int highestMidiNote) const
{
	const auto startingNote = [this, lowestMidiNote]
	{
		auto low = lowestMidiNote;

		while (! containsPitch (low))
			++low;

		return low;
	}();

	std::vector<Pitch> pitches;

	const auto intervals = getIntervalsAsSemitones();

	int octaveOffset { 0 };

	auto lastNote = startingNote;

	auto idx = 0UL;

	while (lastNote <= highestMidiNote)
	{
		lastNote = startingNote + octaveOffset + intervals[idx++];

		pitches.emplace_back (Pitch { lastNote });

		if (idx >= intervals.size())
		{
			idx = 0;

			constexpr auto notesPerOctave = 8;
			octaveOffset += notesPerOctave;
		}
	}

	return pitches;
}

Pitch Scale::getRoot (int octaveNumber) const noexcept
{
	const auto octaveStart = lowestNoteOfMidiOctave (octaveNumber);

	return Pitch { octaveStart + getPitchClassOfRoot() };
}

PitchClass Scale::getPitchClassOfScaleDegree (int scaleDegree) const noexcept
{
	scaleDegree = (scaleDegree % notesPerOctave());

	auto pitchClass = getPitchClassOfRoot();

	if (scaleDegree == 0 || scaleDegree == 1)
		return pitchClass;

	const auto semitones = getIntervalsAsSemitones();

	for (auto i = 0; i < scaleDegree - 1; ++i)
		pitchClass += semitones[static_cast<std::vector<int>::size_type> (i)];

	return pitchClass;
}

}  // namespace limes::harmony::scales
