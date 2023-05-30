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

include (FetchContent)

FetchContent_Declare (
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG origin/devel
	GIT_SHALLOW ON
	FIND_PACKAGE_ARGS 3 GLOBAL)

FetchContent_MakeAvailable (Catch2)

if (catch2_SOURCE_DIR)
	list (APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
endif ()

include (Catch)

add_executable (lharmony_tests)

set_target_properties (lharmony_tests PROPERTIES MACOSX_BUNDLE OFF)

target_sources (lharmony_tests PRIVATE CompoundInterval.cpp Interval.cpp KeySignature.cpp Mode.cpp
									   Pitch.cpp PitchUtils.cpp)

target_link_libraries (lharmony_tests PRIVATE Catch2::Catch2WithMain limes::lharmony)

if (WIN32)
	add_custom_command (
		TARGET lharmony_tests POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy -t $<TARGET_FILE_DIR:lharmony_tests>
				$<TARGET_RUNTIME_DLLS:lharmony_tests> USES_TERMINAL COMMAND_EXPAND_LISTS)
endif ()

# cmake-format: off
catch_discover_tests (
	lharmony_tests
	EXTRA_ARGS
		--warn NoAssertions
		--order rand
		--verbosity high
	TEST_PREFIX "Limes.harmony.unit.")
# cmake-format: on
