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

limes_get_catch2 ()

add_executable (lharmony_tests)

target_sources (lharmony_tests PRIVATE CompoundInterval.cpp Interval.cpp KeySignature.cpp Mode.cpp
                                       Pitch.cpp PitchUtils.cpp)

limes_configure_test_target (
    lharmony_tests
    BUNDLE_ID Limes.lharmony.tests
    VERSION_MAJOR "${lharmony_VERSION_MAJOR}"
    FULL_VERSION "${lharmony_VERSION}"
    TEST_PREFIX limes.harmony.unit.)

target_link_libraries (lharmony_tests PRIVATE limes::lharmony)

include (FindPackage/CreateTests.cmake)
