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

#include "lharmony/lharmony_PitchClass.h"

namespace limes::harmony
{

// TODO: could use unicode flat/sharp characters...
std::string_view PitchClass::getString (bool useSharps) const noexcept
{
	switch (pitchClass)
	{
		case (0) : return "C";
		case (1) :
		{
			if (useSharps)
				return "C#";

			return "Db";
		}
		case (2) : return "D";
		case (3) :
		{
			if (useSharps)
				return "D#";

			return "Eb";
		}
		case (4) : return "E";
		case (5) : return "F";
		case (6) :
		{
			if (useSharps)
				return "F#";

			return "Gb";
		}
		case (7) : return "G";
		case (8) :
		{
			if (useSharps)
				return "G#";

			return "Ab";
		}
		case (9) : return "A";
		case (10) :
		{
			if (useSharps)
				return "A#";

			return "Bb";
		}
		case (11) : return "B";
	}
}

std::ostream& operator<< (std::ostream& os, const PitchClass& value)
{
	os << value.getString (true);
	return os;
}

}  // namespace limes::harmony
