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

#include "lharmony/lharmony.h"
#include <catch2/catch_all.hpp>

#define TAGS "[audio][harmony][pitch]"

namespace harmony = limes::harmony;
using Pitch		  = harmony::Pitch;
using PitchClass  = harmony::PitchClass;

TEST_CASE ("Pitch - frequency conversion", TAGS)
{
	const auto freq = GENERATE (378., 501., 698., 1523.);

	INFO ("Frequency: " << freq);

	const auto p = Pitch::fromFreq (freq);

	REQUIRE_THAT (p.getFreqHz(),
				  Catch::Matchers::WithinAbs (freq, 0.01));
}

TEST_CASE ("Pitch - MIDI conversion", TAGS)
{
	const auto pitch = GENERATE (23, 69, 108, 376, 0, -12);

	INFO ("MIDI pitch: " << pitch);

	const auto p = Pitch::fromMIDI (pitch);

	REQUIRE (p.getMidiPitch() == pitch);
}

TEST_CASE ("Pitch - PitchClass conversion", TAGS)
{
	const auto pitchClass = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

	INFO ("Pitch class: " << pitchClass);

	const PitchClass pc { pitchClass };

	REQUIRE (pc.getAsInt() == pitchClass);

	const auto octave = GENERATE (0, 1, 2, 3, 4, 5, 6, 7);

	INFO ("Octave: " << octave);

	const auto pitch = Pitch::fromPitchClass (pc, octave);

	REQUIRE (pitch.getPitchClass() == pc);
	REQUIRE (pitch.getOctaveNumber() == octave);
}

TEST_CASE ("Pitch - octave number", TAGS)
{
	const auto midi = GENERATE (0, 127, 64, 63, 31, 86);

	INFO ("MIDI pitch: " << midi);

	const Pitch pitch { midi };

	const auto octave = pitch.getOctaveNumber();

	REQUIRE (harmony::octaveNumberOfMidiNote (midi) == octave);
	REQUIRE (harmony::lowestNoteOfMidiOctave (octave) <= midi);
	REQUIRE (harmony::highestNoteOfMidiOctave (octave) >= midi);

	const auto upOctave = pitch.inOctave (octave + 1);

	REQUIRE (upOctave > pitch);
	REQUIRE (upOctave.getRoundedMidiPitch() == midi + 12);

	const auto downOctave = pitch.inOctave (octave - 1);

	REQUIRE (downOctave < pitch);
	REQUIRE (downOctave.getRoundedMidiPitch() == midi - 12);
}

TEST_CASE ("Pitch - black/white keys", TAGS)
{
	SECTION ("Known black keys")
	{
		const auto midi = GENERATE (20, 30, 63, 70, 104, 126);

		INFO ("MIDI pitch: " << midi);

		const Pitch p { midi };

		REQUIRE (p.isBlackKey());
		REQUIRE (! p.isWhiteKey());
	}

	SECTION ("Known white keys")
	{
		const auto midi = GENERATE (21, 48, 72, 105, 127);

		INFO ("MIDI pitch: " << midi);

		const Pitch p { midi };

		REQUIRE (p.isWhiteKey());
		REQUIRE (! p.isBlackKey());
	}
}

#undef TAGS
