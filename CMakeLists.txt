cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PI_PROJECT_VERSION 0.1)

project(PrimeIdeal VERSION ${PI_PROJECT_VERSION}
                  DESCRIPTION "Low-level C calculation library"
                  LANGUAGES C)
                  
if( NOT DEFINED PI_BUILD_TESTS )
set(PI_BUILD_TESTS 0)
endif()
                  
if( ${PI_BUILD_TESTS} )
set(PI_SOURCE_FILES source/output.c source/test_utils.c)
set(PI_HEADER_FILES include/definitions.h include/output.h include/utilities.h include/pi_exports.h include/test_utils.h)
else()
set(PI_SOURCE_FILES source/output.c)
set(PI_HEADER_FILES include/definitions.h include/output.h include/utilities.h include/pi_exports.h)
endif()

add_library(PrimeIdeal SHARED ${PI_SOURCE_FILES} ${PI_HEADER_FILES})
target_include_directories(PrimeIdeal PUBLIC include)
set_target_properties(PrimeIdeal PROPERTIES VERSION ${PI_PROJECT_VERSION})
target_compile_features(PrimeIdeal PUBLIC c_std_17)
include(GenerateExportHeader)
generate_export_header(PrimeIdeal
    EXPORT_MACRO_NAME PRIMEIDEAL_EXPORT
    EXPORT_FILE_NAME pi_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

if( ${PI_BUILD_TESTS} )

add_executable(test_runner testing/test_runner.c)
target_include_directories(test_runner PUBLIC include)
target_link_libraries(test_runner PUBLIC PrimeIdeal)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test_runner)

endif()

