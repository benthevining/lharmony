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

#include "lharmony/lharmony_Export.h"
#include "lharmony/lharmony_Interval.h"

/** @file
	This file provides some useful Interval objects as constants.

	@ingroup lharmony_intervals
 */

/** This namespace contains some useful Interval objects as constants.

	@ingroup lharmony_intervals
 */
namespace limes::harmony::intervals
{

/** @ingroup lharmony_intervals
	@{
*/

/** This namespace contains perfect interval objects. */
namespace perfect
{

/** A perfect unison. */
LHARM_EXPORT static constexpr Interval unison { 0, Interval::Quality::Perfect };

/** A perfect fourth. */
LHARM_EXPORT static constexpr Interval fourth { 4, Interval::Quality::Perfect };

/** A perfect fifth. */
LHARM_EXPORT static constexpr Interval fifth { 5, Interval::Quality::Perfect };

/** A perfect octave. */
LHARM_EXPORT static constexpr Interval octave { 8, Interval::Quality::Perfect };

}  // namespace perfect

/** This namespace contains diminished interval objects. */
namespace diminished
{

/** A diminished second. */
LHARM_EXPORT static constexpr Interval second { 2, Interval::Quality::Diminished };

/** A diminished third. */
LHARM_EXPORT static constexpr Interval third { 3, Interval::Quality::Diminished };

/** A diminished fourth. */
LHARM_EXPORT static constexpr Interval fourth { 4, Interval::Quality::Diminished };

/** A diminished fifth. */
LHARM_EXPORT static constexpr Interval fifth { 5, Interval::Quality::Diminished };

/** A diminished sixth. */
LHARM_EXPORT static constexpr Interval sixth { 6, Interval::Quality::Diminished };

/** A diminished seventh. */
LHARM_EXPORT static constexpr Interval seventh { 7, Interval::Quality::Diminished };

/** A diminished octave. */
LHARM_EXPORT static constexpr Interval octave { 8, Interval::Quality::Diminished };

}  // namespace diminished

/** This namespace contains minor interval objects. */
namespace minor
{

/** A minor second. */
LHARM_EXPORT static constexpr Interval second { 2, Interval::Quality::Minor };

/** A minor third. */
LHARM_EXPORT static constexpr Interval third { 3, Interval::Quality::Minor };

/** A minor sixth. */
LHARM_EXPORT static constexpr Interval sixth { 6, Interval::Quality::Minor };

/** A minor seventh. */
LHARM_EXPORT static constexpr Interval seventh { 7, Interval::Quality::Minor };

}  // namespace minor

/** This namespace contains major interval objects. */
namespace major
{

/** A major second. */
LHARM_EXPORT static constexpr Interval second { 2, Interval::Quality::Major };

/** A major third. */
LHARM_EXPORT static constexpr Interval third { 3, Interval::Quality::Major };

/** A major sixth. */
LHARM_EXPORT static constexpr Interval sixth { 6, Interval::Quality::Major };

/** A major seventh. */
LHARM_EXPORT static constexpr Interval seventh { 7, Interval::Quality::Major };

}  // namespace major

/** This namespace contains augmented interval objects. */
namespace augmented
{

/** An augmented unison. */
LHARM_EXPORT static constexpr Interval unison { 0, Interval::Quality::Augmented };

/** An augmented second. */
LHARM_EXPORT static constexpr Interval second { 2, Interval::Quality::Augmented };

/** An augmented third. */
LHARM_EXPORT static constexpr Interval third { 3, Interval::Quality::Augmented };

/** An augmented fourth. */
LHARM_EXPORT static constexpr Interval fourth { 4, Interval::Quality::Augmented };

/** An augmented fifth. */
LHARM_EXPORT static constexpr Interval fifth { 5, Interval::Quality::Augmented };

/** An augmented sixth. */
LHARM_EXPORT static constexpr Interval sixth { 6, Interval::Quality::Augmented };

/** An augmented seventh. */
LHARM_EXPORT static constexpr Interval seventh { 7, Interval::Quality::Augmented };

/** An augmented octave. */
LHARM_EXPORT static constexpr Interval octave { 8, Interval::Quality::Augmented };

}  // namespace augmented

/** @} */

}  // namespace limes::harmony::intervals
