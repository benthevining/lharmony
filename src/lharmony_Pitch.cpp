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
#include "lharmony/lharmony_Pitch.h"
#include "lharmony/lharmony_PitchClass.h"
#include "lharmony/lharmony_PitchUtils.h"
#include "lharmony/lharmony_Interval.h"

namespace limes::harmony
{

template <ArithmeticType T>
[[nodiscard]] static inline int round (T input) noexcept
{
	return static_cast<int> (std::round (input));
}

Interval Pitch::operator- (const Pitch& other) const noexcept
{
	return Interval::fromPitches (*this, other);
}

bool Pitch::approximatelyEqual (Pitch other) const noexcept
{
	return round (midiPitch) == round (other.midiPitch);
}

int Pitch::getRoundedFreqHz() const noexcept
{
	return round (getFreqHz());
}

double Pitch::getFreqHz() const noexcept
{
	return midiToFreq (midiPitch);
}

int Pitch::getRoundedMidiPitch() const noexcept
{
	return round (midiPitch);
}

PitchClass Pitch::getPitchClass() const noexcept
{
	return PitchClass { round (midiPitch) };
}

int Pitch::getOctaveNumber() const noexcept
{
	return octaveNumberOfMidiNote (round (midiPitch));
}

bool Pitch::isBlackKey() const noexcept
{
	return getPitchClass().isBlackKey();
}

bool Pitch::isWhiteKey() const noexcept
{
	return ! isBlackKey();
}

bool Pitch::isMicrotone() const noexcept
{
	return std::floor (midiPitch) != midiPitch;
}

Pitch Pitch::inOctave (int octaveNumber) const noexcept
{
	return Pitch { getPitchClass(), octaveNumber };
}

std::ostream& operator<< (std::ostream& os, const Pitch& value)
{
	os << value.getMidiPitch();
	return os;
}

}  // namespace limes::harmony
