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
#include "lharmony/lharmony_KeySignature.h"

/** @file
	This file contains some useful predefined key signatures.

	@ingroup lharmony_scales
 */

/** This namespace contains some useful predefined key signatures.

	@ingroup lharmony_scales
 */
namespace limes::harmony::scales::keys
{

/** @ingroup lharmony_scales
	@{
*/

/** This namespace contains major keys. */
namespace major
{

/** A C major scale. */
LHARM_EXPORT static constexpr KeySignature c { 0, false, KeySignature::Type::Major };

/** A C-sharp major scale. */
LHARM_EXPORT static constexpr KeySignature cSharp { 7, true, KeySignature::Type::Major };

/** A C-flat major scale. */
LHARM_EXPORT static constexpr KeySignature cFlat { 7, false, KeySignature::Type::Major };

/** A D major scale. */
LHARM_EXPORT static constexpr KeySignature d { 2, true, KeySignature::Type::Major };

/** A D-flat major scale. */
LHARM_EXPORT static constexpr KeySignature dFlat { 5, false, KeySignature::Type::Major };

/** An E major scale. */
LHARM_EXPORT static constexpr KeySignature e { 4, true, KeySignature::Type::Major };

/** An E-flat major scale. */
LHARM_EXPORT static constexpr KeySignature eFlat { 3, false, KeySignature::Type::Major };

/** An F major scale. */
LHARM_EXPORT static constexpr KeySignature f { 1, false, KeySignature::Type::Major };

/** An F-sharp major scale. */
LHARM_EXPORT static constexpr KeySignature fSharp { 6, true, KeySignature::Type::Major };

/** A G major scale. */
LHARM_EXPORT static constexpr KeySignature g { 1, true, KeySignature::Type::Major };

/** A G-flat major scale. */
LHARM_EXPORT static constexpr KeySignature gFlat { 6, false, KeySignature::Type::Major };

/** An A major scale. */
LHARM_EXPORT static constexpr KeySignature a { 3, true, KeySignature::Type::Major };

/** An A-flat major scale. */
LHARM_EXPORT static constexpr KeySignature aFlat { 4, false, KeySignature::Type::Major };

/** A B major scale. */
LHARM_EXPORT static constexpr KeySignature b { 5, true, KeySignature::Type::Major };

/** A B-flat major scale. */
LHARM_EXPORT static constexpr KeySignature bFlat { 2, false, KeySignature::Type::Major };

}  // namespace major

/** This namespace contains natural minor keys. */
namespace natural_minor
{

/** A C minor scale. */
LHARM_EXPORT static constexpr KeySignature c { 3, false, KeySignature::Type::NaturalMinor };

/** A C-sharp minor scale. */
LHARM_EXPORT static constexpr KeySignature cSharp { 4, true, KeySignature::Type::NaturalMinor };

/** A D minor scale. */
LHARM_EXPORT static constexpr KeySignature d { 1, false, KeySignature::Type::NaturalMinor };

/** A D-sharp minor scale. */
LHARM_EXPORT static constexpr KeySignature dSharp { 6, true, KeySignature::Type::NaturalMinor };

/** An E minor scale. */
LHARM_EXPORT static constexpr KeySignature e { 1, true, KeySignature::Type::NaturalMinor };

/** An E-flat minor scale. */
LHARM_EXPORT static constexpr KeySignature eFlat { 6, false, KeySignature::Type::NaturalMinor };

/** An F minor scale. */
LHARM_EXPORT static constexpr KeySignature f { 4, false, KeySignature::Type::NaturalMinor };

/** An F-sharp minor scale. */
LHARM_EXPORT static constexpr KeySignature fSharp { 3, true, KeySignature::Type::NaturalMinor };

/** A G minor scale. */
LHARM_EXPORT static constexpr KeySignature g { 2, false, KeySignature::Type::NaturalMinor };

/** A G-sharp minor scale. */
LHARM_EXPORT static constexpr KeySignature gSharp { 5, true, KeySignature::Type::NaturalMinor };

/** An A minor scale. */
LHARM_EXPORT static constexpr KeySignature a { 0, false, KeySignature::Type::NaturalMinor };

/** An A-sharp minor scale. */
LHARM_EXPORT static constexpr KeySignature aSharp { 7, true, KeySignature::Type::NaturalMinor };

/** An A-flat minor scale. */
LHARM_EXPORT static constexpr KeySignature aFlat { 7, false, KeySignature::Type::NaturalMinor };

/** A B minor scale. */
LHARM_EXPORT static constexpr KeySignature b { 2, true, KeySignature::Type::NaturalMinor };

/** A B-flat minor scale. */
LHARM_EXPORT static constexpr KeySignature bFlat { 5, false, KeySignature::Type::NaturalMinor };

}  // namespace natural_minor

/** A convenience alias to access the minor keys with simply 'minor'. */
namespace minor = natural_minor;

/** This namespace contains harmonic minor keys. */
namespace harmonic_minor
{

/** A C harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature c { 3, false, KeySignature::Type::HarmonicMinor };

/** A C-sharp harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature cSharp { 4, true, KeySignature::Type::HarmonicMinor };

/** A D harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature d { 1, false, KeySignature::Type::HarmonicMinor };

/** A D-sharp harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature dSharp { 6, true, KeySignature::Type::HarmonicMinor };

/** An E harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature e { 1, true, KeySignature::Type::HarmonicMinor };

/** An E-flat harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature eFlat { 6, false, KeySignature::Type::HarmonicMinor };

/** An F harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature f { 4, false, KeySignature::Type::HarmonicMinor };

/** An F-sharp harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature fSharp { 3, true, KeySignature::Type::HarmonicMinor };

/** A G harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature g { 2, false, KeySignature::Type::HarmonicMinor };

/** A G-sharp harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature gSharp { 5, true, KeySignature::Type::HarmonicMinor };

/** An A harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature a { 0, false, KeySignature::Type::HarmonicMinor };

/** An A-sharp harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature aSharp { 7, true, KeySignature::Type::HarmonicMinor };

/** An A-flat harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature aFlat { 7, false, KeySignature::Type::HarmonicMinor };

/** A B harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature b { 2, true, KeySignature::Type::HarmonicMinor };

/** A B-flat harmonic minor scale. */
LHARM_EXPORT static constexpr KeySignature bFlat { 5, false, KeySignature::Type::HarmonicMinor };

}  // namespace harmonic_minor

/** @} */

}  // namespace limes::harmony::scales::keys
