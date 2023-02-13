#include "definitions.h"
#include "utilities.h"

#include "test_utils.h"

#include <stddef.h>

void output_test(test_case test)
{
    if (test.run_test != NULL)
    {
        integer run_result = test.run_test();
        integer expected_result = test.expected_result;
        if (expected_result == run_result)
        {
            output_line("PASSED!");
        }
        else
        {
            if (0 == expected_result)
            {
                output_line("POSSIBLY CORRECT");
            }
            else
            {
                output_text("FAILED! Expected: ");
                output_integer(expected_result);
                output_text(" Result: ");
                output_integer(run_result);
                output_newline();
            }
        }
    }
    else
    {
        output_line("UNIMPLEMENTED");
    }

}

DECLARE_STACK_HELPERS(int)
DECLARE_STACK_HELPERS(float)

integer run_utility_test()
{
    
    {
        output_line("Testing int array...");

        int* new_array = NULL;
        new_array = allocate_int_array(3);
        assert(new_array != NULL);
        assert(new_array[1] != 42);
        deallocate_int_array(&new_array);

        new_array = initialize_int_array(3, 42);
        assert(new_array != NULL);
        assert(new_array[1] == 42);
        deallocate_int_array(&new_array);
        assert(new_array == NULL);

        output_line("...passed!");

        output_line("Testing int buffer...");

        int_buffer new_buffer = make_int_buffer(0, 42);
        assert(new_buffer.typed_array == NULL);
        assert(new_buffer.size == 0);

        new_buffer = make_int_buffer(4, 42);
        assert(new_buffer.typed_array != NULL);
        assert(new_buffer.size == 4);
        assert(get_int_from_buffer(new_buffer, 0) == 42);
        assert(get_int_from_buffer(new_buffer, 1) == 42);
        assert(get_int_from_buffer(new_buffer, 2) == 42);
        assert(get_int_from_buffer(new_buffer, 3) == 42);

        set_int_in_buffer(new_buffer, 2, 101);
        assert(get_int_from_buffer(new_buffer, 2) == 101);
        assert(get_int_from_buffer(new_buffer, 3) == 42);
        assert(get_int_from_buffer(new_buffer, 1) == 42);

        destroy_int_buffer(&new_buffer);
        assert(new_buffer.typed_array == NULL);
        assert(new_buffer.size == 0);

        output_line("...passed!");

        output_line("Testing int stack...");
        int_stack test_stack = make_int_stack();
        assert(test_stack.buffer.typed_array != NULL);
        assert(test_stack.buffer.size != 0);
        assert(test_stack.height == 0);

        push_int(&test_stack, 1);
        push_int(&test_stack, 2);
        assert(test_stack.buffer.typed_array != NULL);
        assert(test_stack.buffer.size != 0);
        assert(test_stack.height == 2);

        assert(pop_int(&test_stack) == 2);
        assert(pop_int(&test_stack) == 1);
        assert(int_stack_is_empty(test_stack));
        assert(test_stack.height == 0);

        push_int(&test_stack, 1);
        push_int(&test_stack, 2);
        push_int(&test_stack, 3);
        push_int(&test_stack, 4);
        push_int(&test_stack, 5);
        push_int(&test_stack, 6);
        push_int(&test_stack, 7);
        assert(test_stack.height == 7);

        assert(pop_int(&test_stack) == 7);
        assert(pop_int(&test_stack) == 6);
        assert(test_stack.height == 5);

        push_int(&test_stack, 8);
        push_int(&test_stack, 9);
        push_int(&test_stack, 10);
        push_int(&test_stack, 11);
        push_int(&test_stack, 12);
        push_int(&test_stack, 13);
        assert(test_stack.height == 11);

        assert(pop_int(&test_stack) == 13);
        assert(pop_int(&test_stack) == 12);
        assert(pop_int(&test_stack) == 11);
        assert(test_stack.height == 8);

        push_int(&test_stack, 14);
        push_int(&test_stack, 15);
        push_int(&test_stack, 16);
        push_int(&test_stack, 17);
        assert(test_stack.height == 12);

        assert(pop_int(&test_stack) == 17);
        assert(pop_int(&test_stack) == 16);
        assert(pop_int(&test_stack) == 15);
        assert(pop_int(&test_stack) == 14);
        assert(pop_int(&test_stack) == 10);
        assert(pop_int(&test_stack) == 9);
        assert(pop_int(&test_stack) == 8);
        assert(pop_int(&test_stack) == 5);
        assert(pop_int(&test_stack) == 4);
        assert(pop_int(&test_stack) == 3);
        assert(pop_int(&test_stack) == 2);
        assert(pop_int(&test_stack) == 1);

        destroy_int_stack(&test_stack);
        assert(test_stack.buffer.typed_array == NULL);
        assert(test_stack.buffer.size == 0);
        assert(test_stack.height == 0);


        output_line("...passed!");
    }
    {
        output_line("Testing float array...");

        float* new_array = NULL;
        new_array = allocate_float_array(3);
        assert(new_array != NULL);
        assert(new_array[1] != 42);
        deallocate_float_array(&new_array);

        new_array = initialize_float_array(3, 42.0f);
        assert(new_array != NULL);
        assert(new_array[1] == 42.0f);
        deallocate_float_array(&new_array);
        assert(new_array == NULL);

        output_line("...passed!");

        output_line("Testing float buffer...");

        float_buffer new_buffer = make_float_buffer(0, 42.0f);
        assert(new_buffer.typed_array == NULL);
        assert(new_buffer.size == 0);

        new_buffer = make_float_buffer(4, 42.0f);
        assert(new_buffer.typed_array != NULL);
        assert(new_buffer.size == 4);
        assert(get_float_from_buffer(new_buffer, 0) == 42.0f);
        assert(get_float_from_buffer(new_buffer, 1) == 42.0f);
        assert(get_float_from_buffer(new_buffer, 2) == 42.0f);
        assert(get_float_from_buffer(new_buffer, 3) == 42.0f);

        set_float_in_buffer(new_buffer, 2, 101.0f);
        assert(get_float_from_buffer(new_buffer, 2) == 101.0f);
        assert(get_float_from_buffer(new_buffer, 3) == 42.0f);
        assert(get_float_from_buffer(new_buffer, 1) == 42.0f);

        destroy_float_buffer(&new_buffer);
        assert(new_buffer.typed_array == NULL);
        assert(new_buffer.size == 0);

        output_line("...passed!");

        output_line("Testing float stack...");
        float_stack test_stack = make_float_stack();
        assert(test_stack.buffer.typed_array != NULL);
        assert(test_stack.buffer.size != 0);
        assert(test_stack.height == 0);

        push_float(&test_stack, 1.0f);
        push_float(&test_stack, 2.0f);
        assert(test_stack.buffer.typed_array != NULL);
        assert(test_stack.buffer.size != 0);
        assert(test_stack.height == 2);

        assert(pop_float(&test_stack) == 2.0f);
        assert(pop_float(&test_stack) == 1.0f);
        assert(float_stack_is_empty(test_stack));
        assert(test_stack.height == 0);

        push_float(&test_stack, 1.0f);
        push_float(&test_stack, 2.0f);
        push_float(&test_stack, 3.0f);
        push_float(&test_stack, 4.0f);
        push_float(&test_stack, 5.0f);
        push_float(&test_stack, 6.0f);
        push_float(&test_stack, 7.0f);
        assert(test_stack.height == 7);

        assert(pop_float(&test_stack) == 7.0f);
        assert(pop_float(&test_stack) == 6.0f);
        assert(test_stack.height == 5);

        push_float(&test_stack, 8.0f);
        push_float(&test_stack, 9.0f);
        push_float(&test_stack, 10.0f);
        push_float(&test_stack, 11.0f);
        push_float(&test_stack, 12.0f);
        push_float(&test_stack, 13.0f);
        assert(test_stack.height == 11);

        assert(pop_float(&test_stack) == 13.0f);
        assert(pop_float(&test_stack) == 12.0f);
        assert(pop_float(&test_stack) == 11.0f);
        assert(test_stack.height == 8);

        push_float(&test_stack, 14.0f);
        push_float(&test_stack, 15.0f);
        push_float(&test_stack, 16.0f);
        push_float(&test_stack, 17.0f);
        assert(test_stack.height == 12);

        assert(pop_float(&test_stack) == 17.0f);
        assert(pop_float(&test_stack) == 16.0f);
        assert(pop_float(&test_stack) == 15.0f);
        assert(pop_float(&test_stack) == 14.0f);
        assert(pop_float(&test_stack) == 10.0f);
        assert(pop_float(&test_stack) == 9.0f);
        assert(pop_float(&test_stack) == 8.0f);
        assert(pop_float(&test_stack) == 5.0f);
        assert(pop_float(&test_stack) == 4.0f);
        assert(pop_float(&test_stack) == 3.0f);
        assert(pop_float(&test_stack) == 2.0f);
        assert(pop_float(&test_stack) == 1.0f);

        destroy_float_stack(&test_stack);
        assert(test_stack.buffer.typed_array == NULL);
        assert(test_stack.buffer.size == 0);
        assert(test_stack.height == 0);


        output_line("...passed!");
    }

    return 1;
}
