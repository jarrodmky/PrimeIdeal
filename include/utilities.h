#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

#define DECLARE_ARRAY_HELPERS(type) \
type* allocate_##type##_array(size_t initial_size) \
{ \
    if(initial_size > 0) \
    { \
        type* new_array = malloc(initial_size * sizeof(type)); \
        assert(new_array != NULL); \
        return new_array; \
    } \
    return NULL; \
} \
 \
type* initialize_##type##_array(size_t initial_size, type initial_value) \
{ \
    if(initial_size > 0) \
    { \
        type* new_array = malloc(initial_size * sizeof(type)); \
        assert(new_array != NULL); \
        for(size_t index = 0; index < initial_size; ++index) \
        { \
            new_array[index] = initial_value; \
        } \
        return new_array; \
    } \
    return NULL; \
} \
 \
void deallocate_##type##_array(type** some_array_ptr) \
{ \
    assert(*some_array_ptr != NULL); \
    free(*some_array_ptr); \
    *some_array_ptr = NULL; \
}

#define DECLARE_BUFFER_HELPERS(type) \
DECLARE_ARRAY_HELPERS(type) \
typedef struct \
{ \
    type* typed_array;\
    size_t size; \
} type##_buffer; \
\
type##_buffer make_##type##_buffer(size_t initial_size, type initial_value) \
{ \
   type##_buffer new_buffer; \
   new_buffer.typed_array=initialize_##type##_array(initial_size, initial_value); \
   new_buffer.size = initial_size; \
   return new_buffer; \
} \
 \
void destroy_##type##_buffer(type##_buffer* buffer) \
{ \
    deallocate_##type##_array(&buffer->typed_array); \
    buffer->size = 0; \
} \
\
type get_##type##_from_buffer(type##_buffer buffer, size_t index) \
{ \
    assert(buffer.size > index); \
    return buffer.typed_array[index]; \
} \
\
void set_##type##_in_buffer(type##_buffer buffer, size_t index, type value) \
{ \
    assert(buffer.size > index); \
    buffer.typed_array[index] = value; \
}

#define DECLARE_STACK_HELPERS(type) \
DECLARE_BUFFER_HELPERS(type) \
typedef struct \
{ \
    type##_buffer buffer;\
    size_t height; \
} type##_stack; \
\
type##_stack make_##type##_stack() \
{ \
   type##_stack new_stack; \
   new_stack.buffer=make_##type##_buffer(32, 0); \
   new_stack.height = 0; \
   return new_stack; \
} \
 \
void destroy_##type##_stack(type##_stack* stack) \
{ \
    destroy_##type##_buffer(&stack->buffer); \
    stack->height = 0; \
} \
\
bool type##_stack_is_empty(type##_stack stack) \
{ \
    return stack.height == 0; \
} \
 \
type pop_##type(type##_stack* stack) \
{ \
    assert(stack->height > 0); \
    type popped = get_##type##_from_buffer(stack->buffer, --stack->height); \
    return popped; \
} \
 \
void push_##type(type##_stack* stack, type value) \
{ \
    if(stack->height == stack->buffer.size) \
    { \
        type##_buffer old_buffer = stack->buffer; \
        stack->buffer = make_##type##_buffer(old_buffer.size * 2, 0); \
        for(size_t index = 0; index < old_buffer.size; ++index) \
        { \
            stack->buffer.typed_array[index] = old_buffer.typed_array[index]; \
        } \
        destroy_##type##_buffer(&old_buffer); \
    } \
 \
    set_##type##_in_buffer(stack->buffer, stack->height++, value); \
}


