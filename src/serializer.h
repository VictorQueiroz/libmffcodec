#ifndef MFF_C_SERIALIZER_H
#define MFF_C_SERIALIZER_H

#include <stdint.h>

#define MFF_SERIALIZATION_RESULT_OK 0
#define MFF_SERIALIZATION_RESULT_FAILED 1
#define MFF_SERIALIZATION_RESULT_NULL_POINTER 2
#define MFF_SERIALIZATION_RESULT_REALLOCATION_FAILED 3

#ifndef MFF_SERIALIZER_GROW_SIZE
#define MFF_SERIALIZER_GROW_SIZE 1024*8
#endif

#define MFF_SERIALIZER_RETURN_ON_FAILURE(s) \
    if(s->error != MFF_SERIALIZATION_RESULT_OK) return;

#define MFF_SERIALIZER_FAIL_IF_NULL(s, v) \
    if(v == NULL) {\
        mff_serializer_set_error_code(s, MFF_SERIALIZATION_RESULT_NULL_POINTER);\
    }

typedef struct _mff_serializer {
    uint8_t* buffer;
    uint32_t length;
    uint32_t offset;
    uint8_t error;
} mff_serializer;

void mff_serializer_set_error_code(mff_serializer*, uint8_t);
void mff_serializer_init(mff_serializer** serializer);
void mff_serializer_write_int8(mff_serializer*, int8_t value);
void mff_serializer_write_uint8(mff_serializer*, uint8_t value);
void mff_serializer_write_int16(mff_serializer*, int16_t value);
void mff_serializer_write_uint16(mff_serializer*, uint16_t value);
void mff_serializer_write_int32(mff_serializer*, int32_t value);
void mff_serializer_write_uint32(mff_serializer*, uint32_t value);
void mff_serializer_adjust_buffer_length(mff_serializer*, uint32_t length);
void mff_serializer_write_double(mff_serializer*, double value);
void mff_serializer_write_float(mff_serializer*, float value);
void mff_serializer_get_data(mff_serializer*, uint8_t** buffer);
void mff_serializer_destroy(mff_serializer*);
void mff_serializer_write_string(mff_serializer*, const char* string);
void mff_serializer_write_boolean(mff_serializer*, int value);
uint8_t mff_serializer_get_error(mff_serializer*);

#endif //MFF_C_SERIALIZER_H
