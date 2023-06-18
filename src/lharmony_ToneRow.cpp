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

#include "lharmony/lharmony_ToneRow.h"
#include "lharmony/lharmony_PitchUtils.h"
#include <stdexcept>
#include <sstream>
#include <iterator>

namespace limes::harmony
{

void ToneRow::validatePitchClasses() const
{
	// verify that no pitches are repeated
	for (auto i = 0UL; i < 12UL; ++i)
	{
		for (auto j = i + 1UL; j < 12UL; ++j)
		{
			if (pitches[i] == pitches[j])
			{
				std::stringstream str;

				str << "ToneRow: duplicated pitch class " << pitches[i];

				throw std::runtime_error { str.str() };
			}
		}
	}
}

ToneRow::ToneRow (const Pitches& row)
	: pitches(row)
{
	validatePitchClasses();
}

ToneRow::ToneRow (PitchClass one,  PitchClass two, PitchClass three,  PitchClass four,
				  PitchClass five, PitchClass six, PitchClass seven,  PitchClass eight,
				  PitchClass nine, PitchClass ten, PitchClass eleven, PitchClass twelve)
	: pitches ({ one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve })
{
	validatePitchClasses();
}

size_t ToneRow::getIndexOfPitch (PitchClass pitch) const noexcept
{
	return std::distance (pitches.begin(),
						  std::find (pitches.begin(), pitches.end(), pitch));
}

PitchClass ToneRow::getPitchAtIndex (size_t index) const
{
	if (index >= 12UL)
	{
		std::stringstream str;

		str << "ToneRow: Requested index " << index << " is out of range! A ToneRow only contains 12 pitches!";

		throw std::out_of_range { str.str() };
	}

	return pitches[index];
}

PitchClass ToneRow::operator[](size_t index) const
{
	return getPitchAtIndex (index);
}

ToneRow ToneRow::inversion() const
{
	auto newPitches = pitches;

	newPitches[0UL] = pitches.front();

	for (auto idx = 1UL; idx < 12UL; ++idx)
	{
		const auto orig = pitches[idx];
		const auto last = pitches[idx - 1UL];

		const auto dist = orig.getAsInt() - last.getAsInt();

//		const auto newAsInt = newPitches[idx - 1UL].getAsInt() - dist;

		newPitches[idx] = newPitches[idx - 1UL] - dist;
	}

	return ToneRow { newPitches };
}

ToneRow ToneRow::retrograde() const
{
	ToneRow result { *this };

	std::reverse (result.pitches.begin(),
				  result.pitches.end());

	return result;
}

ToneRow ToneRow::retrogradeInversion() const
{
	return inversion().retrograde();
}

ToneRow ToneRow::transposition (const Interval& interval, bool up) const
{
	const auto st = up ? interval.getNumSemitones() : -interval.getNumSemitones();

	return transposition (st);
}

ToneRow ToneRow::transposition (int numSemitones) const
{
	ToneRow result { *this };

	std::transform (result.pitches.begin(),
					result.pitches.end(),
					result.pitches.begin(),
					[numSemitones](PitchClass pc){ return pc + numSemitones; });

	return result;
}

const ToneRow::Pitches& ToneRow::getPitchClasses() const noexcept
{
	return pitches;
}

bool ToneRow::operator== (const ToneRow& other) const noexcept
{
	return pitches == other.pitches;
}

bool ToneRow::operator!= (const ToneRow& other) const noexcept
{
	return pitches != other.pitches;
}

ToneRow::iterator ToneRow::begin() noexcept
{
	return pitches.begin();
}

ToneRow::iterator ToneRow::end() noexcept
{
	return pitches.end();
}

ToneRow::const_iterator ToneRow::begin() const noexcept
{
	return pitches.cbegin();
}

ToneRow::const_iterator ToneRow::end() const noexcept
{
	return pitches.cend();
}

ToneRow::reverse_iterator ToneRow::rbegin() noexcept
{
	return pitches.rbegin();
}

ToneRow::reverse_iterator ToneRow::rend() noexcept
{
	return pitches.rend();
}

ToneRow::const_reverse_iterator ToneRow::rbegin() const noexcept
{
	return pitches.crbegin();
}

ToneRow::const_reverse_iterator ToneRow::rend() const noexcept
{
	return pitches.crend();
}

}
