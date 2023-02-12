#include "output.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
    test_case utility_test;
    utility_test.run_test = run_utility_test;
    utility_test.expected_result = 1;

    output_test(utility_test);

    return 0;
}
