#pragma once

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

inline uint8_t* allocate_dynamic_array(size_t element_count, size_t element_alignment, size_t element_size)
{
    if(element_count > 0 && element_size > 0)
    {
#ifdef _MSC_VER
        uint8_t* new_array = (uint8_t*)_aligned_malloc(element_count * element_size, element_alignment);
#else
        uint8_t* new_array = (uint8_t*)aligned_alloc(element_alignment, element_count * element_size);
#endif
        assert(new_array != NULL);
        return new_array;
    }
    return NULL;
}

inline uint8_t* initialize_dynamic_array(size_t element_count, const uint8_t* element_value, size_t element_alignment, size_t element_size)
{
    uint8_t* new_array = allocate_dynamic_array(element_count, element_alignment, element_size);
    if(new_array)
    {
        for(size_t index = 0; index < element_count; ++index)
        {
            memcpy(new_array + (index * element_size), element_value, element_size);
        }
        return new_array;
    }
    return NULL;
}

inline void deallocate_dynamic_array(uint8_t** some_array_ptr)
{
    assert(*some_array_ptr != NULL);
#ifdef _MSC_VER
    _aligned_free(*some_array_ptr);
#else
    free(*some_array_ptr);
#endif
    *some_array_ptr = NULL;
}

#define DECLARE_ARRAY_HELPERS(gentype) \
inline gentype* allocate_##gentype##_array(size_t element_count) \
{ \
    return (gentype*)allocate_dynamic_array(element_count, _Alignof(gentype), sizeof(gentype)); \
} \
 \
inline gentype* initialize_##gentype##_array(size_t element_count, gentype initial_value) \
{ \
    return (gentype*)initialize_dynamic_array(element_count, (uint8_t*)&initial_value, _Alignof(gentype), sizeof(gentype)); \
} \
 \
inline void deallocate_##gentype##_array(gentype** some_array_ptr) \
{ \
    deallocate_dynamic_array((uint8_t**)some_array_ptr); \
}

#define DECLARE_BUFFER_HELPERS(gentype) \
DECLARE_ARRAY_HELPERS(gentype) \
typedef struct \
{ \
    gentype* typed_array;\
    size_t size; \
} gentype##_buffer; \
\
inline gentype##_buffer create_##gentype##_buffer(size_t element_count, gentype initial_value) \
{ \
   gentype##_buffer new_buffer = {initialize_##gentype##_array(element_count, initial_value), element_count}; \
   return new_buffer; \
} \
 \
inline void destroy_##gentype##_buffer(gentype##_buffer* buffer) \
{ \
    deallocate_##gentype##_array(&buffer->typed_array); \
    buffer->size = 0; \
} \
\
inline gentype buffer_get_##gentype(gentype##_buffer buffer, size_t index) \
{ \
    assert(index < buffer.size); \
    return buffer.typed_array[index]; \
} \
\
inline void buffer_set_##gentype(gentype##_buffer buffer, size_t index, gentype value) \
{ \
    assert(index < buffer.size); \
    buffer.typed_array[index] = value; \
}

#define DECLARE_STACK_HELPERS(gentype) \
DECLARE_BUFFER_HELPERS(gentype) \
typedef struct \
{ \
    gentype##_buffer buffer;\
    size_t height; \
} gentype##_stack; \
\
inline gentype##_stack create_##gentype##_stack() \
{ \
   gentype##_stack new_stack = {create_##gentype##_buffer(32, 0), 0}; \
   return new_stack; \
} \
 \
inline void destroy_##gentype##_stack(gentype##_stack* stack) \
{ \
    destroy_##gentype##_buffer(&stack->buffer); \
    stack->height = 0; \
} \
\
inline bool stack_is_empty_##gentype(gentype##_stack stack) \
{ \
    return stack.height == 0; \
} \
 \
inline gentype stack_pop_##gentype(gentype##_stack* stack) \
{ \
    assert(stack->height > 0); \
    gentype popped = buffer_get_##gentype(stack->buffer, --stack->height); \
    return popped; \
} \
 \
inline void stack_push_##gentype(gentype##_stack* stack, gentype value) \
{ \
    if(stack->height == stack->buffer.size) \
    { \
        gentype##_buffer old_buffer = stack->buffer; \
        stack->buffer = create_##gentype##_buffer(old_buffer.size * 2, 0); \
        for(size_t index = 0; index < old_buffer.size; ++index) \
        { \
            stack->buffer.typed_array[index] = old_buffer.typed_array[index]; \
        } \
        destroy_##gentype##_buffer(&old_buffer); \
    } \
 \
    buffer_set_##gentype(stack->buffer, stack->height++, value); \
}


