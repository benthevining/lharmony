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
#include "lharmony/lharmony_Chord.h"
#include "lharmony/lharmony_PitchClass.h"
#include "lharmony/lharmony_Interval.h"
#include "lharmony/lharmony_Scale.h"
#include "lharmony/lharmony_Pitch.h"

namespace limes::harmony
{

Chord::Chord (const std::initializer_list<int>& midiNotes)
{
	std::transform (std::begin (midiNotes), std::end (midiNotes), std::begin (pitches),
					[] (const auto midiNote) { return Pitch { midiNote }; });

	pitches.erase (std::unique (std::begin (pitches), std::end (pitches)), std::end (pitches));

	std::sort (std::begin (pitches), std::end (pitches));
}

Chord::Chord (const std::initializer_list<Pitch>& midiNotes)
	: pitches (midiNotes)
{
	pitches.erase (std::unique (std::begin (pitches), std::end (pitches)), std::end (pitches));

	std::sort (std::begin (pitches), std::end (pitches));
}

int Chord::getNumPitches() const
{
	return static_cast<int> (pitches.size());
}

Pitch Chord::getLowestPitch() const
{
	return *std::min_element (std::begin (pitches), std::end (pitches));
}

Pitch Chord::getHighestPitch() const
{
	return *std::max_element (std::begin (pitches), std::end (pitches));
}

bool Chord::contains (PitchClass pitchClass) const noexcept
{
	return std::find_if (std::begin (pitches), std::end (pitches),
						 [pitchClass] (const Pitch p)
						 { return p.getPitchClass() == pitchClass; })
			!= std::end (pitches);
}

bool Chord::contains (Pitch pitch) const noexcept
{
	return std::find (std::begin (pitches), std::end (pitches), pitch) != std::end (pitches);
}

bool Chord::contains (int midiNote) const noexcept
{
	return std::find_if (std::begin (pitches), std::end (pitches),
						 [midiNote] (const Pitch p)
						 { return p.getRoundedMidiPitch() == midiNote; })
			!= std::end (pitches);
}

bool Chord::fitsInScale (const scales::Scale& scale) const noexcept
{
	return std::all_of (pitches.begin(), pitches.end(),
						[&scale] (const Pitch p)
						{ return scale.containsPitch (p); });
}

std::vector<Interval> Chord::getIntervals() const
{
	std::vector<Interval> intervals;

	for (auto i = 1UL; i < pitches.size(); ++i)
		intervals.push_back (Interval::fromPitches (pitches[i - 1], pitches[i]));

	return intervals;
}

std::vector<PitchClass> Chord::getPitchClasses() const
{
	std::vector<PitchClass> pitchClasses;

	std::transform (std::begin (pitches), std::end (pitches), std::begin (pitchClasses),
					[] (const Pitch pitch) { return pitch.getPitchClass(); });

	pitchClasses.erase (std::unique (std::begin (pitchClasses), std::end (pitchClasses)), std::end (pitchClasses));

	std::sort (std::begin (pitchClasses), std::end (pitchClasses));

	return pitchClasses;
}

int Chord::getNumUniquePitchClasses() const
{
	return static_cast<int> (getPitchClasses().size());
}

std::vector<Pitch> Chord::getPitches() const
{
	return pitches;
}

Chord Chord::applyInterval (Interval interval, bool above)
{
	Chord newChord { *this };

	for (auto i = 0UL; i < newChord.pitches.size(); ++i)
		newChord.pitches[i] = interval.applyToPitch (newChord.pitches[i], above);

	return newChord;
}

}  // namespace limes::harmony
