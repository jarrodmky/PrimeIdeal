@echo off

cmake -DPI_BUILD_TESTS=1 -B Generated -G "Visual Studio 17 2022"
cmake --build Generated --config Release

.\Generated\Release\test_runner
