#include "definitions.h"

typedef integer (*test_function)();

typedef struct
{
    test_function run_test;
    integer expected_result;
}
test_case;

void output_test(test_case test);

integer run_utility_test();
