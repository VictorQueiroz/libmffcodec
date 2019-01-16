#ifndef MFF_C_DESERIALIZER_H
#define MFF_C_DESERIALIZER_H

#include <stdint.h>

#define MFF_DESERIALIZATION_RESULT_OK 1
#define MFF_DESERIALIZATION_UNKNOWN_FAILURE 2
#define MFF_DESERIALIZATION_RESULT_INVALID_READ 3

#define MFF_DESERIALIZER_RETURN_ON_FAILURE(d) \
    if(d->error != MFF_DESERIALIZATION_RESULT_OK) return;

typedef struct {
    uint32_t offset;
    uint32_t length;
    uint8_t error;
    uint8_t* buffer;
} mff_deserializer;

void mff_deserializer_init(mff_deserializer**, uint8_t*, uint32_t);
void mff_deserializer_destroy(mff_deserializer*);
void mff_deserializer_read_uint32(mff_deserializer*, uint32_t*);
void mff_deserializer_read_uint16(mff_deserializer* d, uint16_t*);
void mff_deserializer_read_uint8(mff_deserializer* d, uint8_t*);
void mff_deserializer_read_int32(mff_deserializer*, int32_t*);
void mff_deserializer_read_int16(mff_deserializer*, int16_t*);
void mff_deserializer_read_int8(mff_deserializer* d, int8_t* value_ptr);
void mff_deserializer_read_double(mff_deserializer*, double* value_ptr);
void mff_deserializer_read_float(mff_deserializer*, float* value_ptr);
void mff_deserializer_read_buffer(mff_deserializer* d, uint8_t* buffer_ptr, uint32_t length);
void mff_deserializer_check_offset(mff_deserializer*, uint32_t);
void mff_deserializer_set_error_code(mff_deserializer*, uint8_t);
int mff_deserializer_get_error(mff_deserializer*);

#endif //MFF_C_DESERIALIZER_H
