cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(PrimeIdeal VERSION 0.1
                  DESCRIPTION "Low-level C calculation library"
                  LANGUAGES C)
                  
if( NOT DEFINED PI_BUILD_TESTS )
set(PI_BUILD_TESTS 0)
endif()
                  
if( ${PI_BUILD_TESTS} )
set(PI_SOURCE_FILES source/output.c source/test_utils.c)
set(PI_HEADER_FILES include/definitions.h include/output.h include/utilities.h include/test_utils.h)
else()
set(PI_SOURCE_FILES source/output.c)
set(PI_HEADER_FILES include/definitions.h include/output.h include/utilities.h)
endif()

add_library(primeideal STATIC ${PI_SOURCE_FILES} ${PI_HEADER_FILES})
target_include_directories(primeideal PUBLIC include)
target_compile_features(primeideal PUBLIC c_std_17)

if( ${PI_BUILD_TESTS} )

add_executable(test_runner testing/test_runner.c)
target_include_directories(test_runner PUBLIC include)
target_link_libraries(test_runner PUBLIC primeideal)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test_runner)

endif()

