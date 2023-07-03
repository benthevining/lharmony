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

cmake_minimum_required (VERSION 3.25 FATAL_ERROR)

project (lharmony_findpackage_test VERSION 0.0.1 LANGUAGES CXX)

find_package (lharmony REQUIRED)

add_executable (test)

target_sources (test PRIVATE main.cpp)

target_link_libraries (test PRIVATE limes::lharmony)
