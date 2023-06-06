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

/** @defgroup limes_harmony limes_harmony
	The Limes library of harmony utilities.

	@anchor lib_limes_harmony

	@tableofcontents{HTML,LaTeX,XML}

	@section limes_harmony_overview Overview

	All classes and functions in this module are accessible after linking to the
	\c limes::lharmony library and including \c lharmony.h .

	This library provides classes for working with music theory concepts related
	to harmony.

	@section limes_harmony_design Design goals

	// TODO

	@section limes_harmony_features Features

	// TODO

	@section limes_harmony_examples Examples

	// TODO

	@todo circle of fifths class. Stateful - next(), prev(), +=, -=, etc
	@todo tone row class
	@todo note class that includes pitch & spelling (accidentals)
 */

/** @file
	The main header for the @ref lib_limes_harmony "limes_harmony" library.

	@ingroup limes_harmony
 */

/** @namespace limes::harmony
	Utilities for working with musical harmony.

	This namespace contains all code of the @ref lib_limes_harmony "limes_harmony" library.

	@ingroup limes_harmony
 */

#pragma once

// IWYU pragma: begin_exports
#include "lharmony/lharmony_Version.h"

#include "lharmony/lharmony_Pitch.h"
#include "lharmony/lharmony_PitchClass.h"
#include "lharmony/lharmony_PitchUtils.h"

#include "lharmony/lharmony_Interval.h"
#include "lharmony/lharmony_IntervalConstants.h"
#include "lharmony/lharmony_CompoundInterval.h"
#include "lharmony/lharmony_MicrotonalInterval.h"

#include "lharmony/lharmony_Chord.h"

#include "lharmony/lharmony_Scale.h"
#include "lharmony/lharmony_Chromatic.h"
#include "lharmony/lharmony_KeySignature.h"
#include "lharmony/lharmony_KeySignatureConstants.h"
#include "lharmony/lharmony_Mode.h"
#include "lharmony/lharmony_Octatonic.h"
#include "lharmony/lharmony_WholeTone.h"

#include "lharmony/lharmony_OvertoneSeries.h"
// IWYU pragma: end_exports
