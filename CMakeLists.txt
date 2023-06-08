cmake_minimum_required (VERSION 3.25 FATAL_ERROR)

project (
	lharmony
	VERSION 0.0.1
	LANGUAGES CXX C
	DESCRIPTION "C++ harmony library"
	HOMEPAGE_URL "https://github.com/benthevining/lharmony/")

add_subdirectory (linfra)

limes_default_project_options ()

option (LHARM_TESTS "Build the lharmony tests" "${lharmony_IS_TOP_LEVEL}")

option (LHARM_DOCS "Build the lharmony docs" "${lharmony_IS_TOP_LEVEL}")

include (GNUInstallDirs)

set (LHARM_INSTALL_DEST "${CMAKE_INSTALL_LIBDIR}/cmake/lharmony"
	 CACHE STRING "Path where package files will be installed, relative to the install prefix")

mark_as_advanced (LHARM_INSTALL_DEST LHARM_TESTS LHARM_DOCS)

add_library (lharmony)
add_library (limes::lharmony ALIAS lharmony)

target_compile_features (lharmony PUBLIC cxx_std_20)

set_target_properties (lharmony PROPERTIES DEBUG_POSTFIX -d VERSION "${lharmony_VERSION}"
										   SOVERSION "${lharmony_VERSION_MAJOR}")

set (public_header include/lharmony/lharmony.h)

set (
	private_headers
	include/lharmony/lharmony_Chord.h
	include/lharmony/lharmony_Chromatic.h
	include/lharmony/lharmony_CompoundInterval.h
	include/lharmony/lharmony_CompoundInterval_impl.h
	include/lharmony/lharmony_Interval.h
	include/lharmony/lharmony_IntervalConstants.h
	include/lharmony/lharmony_KeySignature.h
	include/lharmony/lharmony_KeySignature_impl.h
	include/lharmony/lharmony_KeySignatureConstants.h
	include/lharmony/lharmony_MicrotonalInterval.h
	include/lharmony/lharmony_Mode.h
	include/lharmony/lharmony_Octatonic.h
	include/lharmony/lharmony_OvertoneSeries.h
	include/lharmony/lharmony_Pitch.h
	include/lharmony/lharmony_PitchClass.h
	include/lharmony/lharmony_PitchUtils.h
	include/lharmony/lharmony_Scale.h
	include/lharmony/lharmony_WholeTone.h)

set (generated_headers_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/lharmony")

set (export_header "${generated_headers_dir}/lharmony_Export.h")

include (GenerateExportHeader)

# cmake-format: off
generate_export_header (
	lharmony
	EXPORT_MACRO_NAME LHARM_EXPORT
	NO_EXPORT_MACRO_NAME LHARM_NO_EXPORT
	EXPORT_FILE_NAME "${export_header}")
# cmake-format: on

set (version_header "${generated_headers_dir}/lharmony_Version.h")

configure_file ("${CMAKE_CURRENT_LIST_DIR}/cmake/version.in" "${version_header}" @ONLY
				NEWLINE_STYLE UNIX)

target_sources (lharmony # PUBLIC "${public_header}"
				PRIVATE ${private_headers} "${export_header}" "${version_header}")

target_include_directories (
	lharmony
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
		   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
		   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install (FILES "${public_header}" "${export_header}" "${version_header}" ${private_headers}
		 DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/lharmony" COMPONENT lharmony_dev)

if (WIN32)
	target_compile_definitions (lharmony PRIVATE NOMINMAX)
endif ()

add_subdirectory (src)

install (
	TARGETS lharmony
	EXPORT lharmony
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT lharmony NAMELINK_COMPONENT lharmony_dev
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT lharmony_dev
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT lharmony
	INCLUDES
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install (
	EXPORT lharmony
	NAMESPACE limes::
	FILE Targets.cmake
	DESTINATION "${LHARM_INSTALL_DEST}"
	COMPONENT lharmony_dev)

include (CMakePackageConfigHelpers)

write_basic_package_version_file (lharmony-config-version.cmake VERSION "${lharmony_VERSION}"
								  COMPATIBILITY SameMajorVersion)

configure_package_config_file (cmake/lharmony-config.in lharmony-config.cmake
							   INSTALL_DESTINATION "${LHARM_INSTALL_DEST}" NO_SET_AND_CHECK_MACRO)

install (FILES "${CMAKE_CURRENT_BINARY_DIR}/lharmony-config-version.cmake"
			   "${CMAKE_CURRENT_BINARY_DIR}/lharmony-config.cmake"
		 DESTINATION "${LHARM_INSTALL_DEST}" COMPONENT lharmony_dev)

include (CPackComponent)

cpack_add_component (
	lharmony
	DISPLAY_NAME "Limes harmony library"
	DESCRIPTION
		"The Limes C++ musical harmony library. This is the runtime component needed by end users."
	GROUP limes_harmony)

cpack_add_component (
	lharmony_dev
	DISPLAY_NAME "Limes harmony library headers"
	DESCRIPTION
		"Development package for the Limes C++ musical harmony library. This component includes the library's header files and CMake package files."
	GROUP limes_harmony
	DEPENDS lharmony)

cpack_add_component_group (limes_harmony DISPLAY_NAME "Limes harmony"
						   DESCRIPTION "Limes harmony library" PARENT_GROUP limes)

if (LHARM_TESTS)
	enable_testing ()

	add_subdirectory (tests)

	include (CTest)
endif ()

if (LHARM_DOCS)
	add_subdirectory (docs)
endif ()

if (lharmony_IS_TOP_LEVEL)
	include (CPack)
endif ()
