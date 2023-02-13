#pragma once

#include "definitions.h"
#include "pi_exports.h"

typedef integer (*test_function)();

typedef struct
{
    test_function run_test;
    integer expected_result;
}
test_case;

void PRIMEIDEAL_EXPORT output_test(test_case test);

integer PRIMEIDEAL_EXPORT run_utility_test();
