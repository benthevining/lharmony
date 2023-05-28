# ======================================================================================
#  __    ____  __  __  ____  ___
# (  )  (_  _)(  \/  )( ___)/ __)
#  )(__  _)(_  )    (  )__) \__ \
# (____)(____)(_/\/\_)(____)(___/
#
#  This file is part of the Limes open source library and is licensed under the terms of the GNU Public License.
#
#  Commercial licenses are available; contact the maintainers at ben.the.vining@gmail.com to inquire for details.
#
# ======================================================================================

target_sources (
	lharmony
	PRIVATE lharmony_Chord.cpp
			lharmony_Chromatic.cpp
			lharmony_CompoundInterval.cpp
			lharmony_Interval.cpp
			lharmony_KeySignature.cpp
			lharmony_Mode.cpp
			lharmony_Octatonic.cpp
			lharmony_Pitch.cpp
			lharmony_PitchClass.cpp
			lharmony_Scale.cpp
			lharmony_WholeTone.cpp)
