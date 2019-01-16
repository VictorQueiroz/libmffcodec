#include "deserializer.h"
#include "ieee754.h"

#include <stdlib.h>
#include <string.h>

void mff_deserializer_init(mff_deserializer** d_ptr, uint8_t* buffer, uint32_t length) {
    *d_ptr = calloc(1, sizeof(mff_deserializer));
    (*d_ptr)->length = length;
    (*d_ptr)->buffer = buffer;
    (*d_ptr)->error = MFF_DESERIALIZATION_RESULT_OK;
}

void mff_deserializer_destroy(mff_deserializer* d) {
    free(d);
}

int mff_deserializer_get_error(mff_deserializer* d) {
    return d->error;
}

void mff_deserializer_set_error_code(mff_deserializer* d, uint8_t error) {
    if(d->error != MFF_DESERIALIZATION_RESULT_OK) {
        return;
    }
    d->error = error;
}

void mff_deserializer_check_offset(mff_deserializer* d, uint32_t l) {
    if((d->offset + l) > d->length) {
        mff_deserializer_set_error_code(d, MFF_DESERIALIZATION_RESULT_INVALID_READ);
    }
}

void mff_deserializer_read_uint32(mff_deserializer* d, uint32_t* value_ptr) {
    mff_deserializer_check_offset(d, 4);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);

    *value_ptr = 0;
    *value_ptr += d->buffer[d->offset++];
    *value_ptr += d->buffer[d->offset++] << 8;
    *value_ptr += d->buffer[d->offset++] << 16;
    *value_ptr += d->buffer[d->offset++] << 24;
}

void mff_deserializer_read_uint16(mff_deserializer* d, uint16_t* value_ptr) {
    mff_deserializer_check_offset(d, 4);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);

    *value_ptr += d->buffer[d->offset++];
    *value_ptr += d->buffer[d->offset++] << 8;
}

void mff_deserializer_read_uint8(mff_deserializer* d, uint8_t* value_ptr) {
    mff_deserializer_check_offset(d, 1);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);

    *value_ptr = d->buffer[d->offset++];
}

void mff_deserializer_read_int32(mff_deserializer* d, int32_t* value_ptr) {
    mff_deserializer_read_uint32(d, (uint32_t*) value_ptr);
}

void mff_deserializer_read_int16(mff_deserializer* d, int16_t* value_ptr) {
    mff_deserializer_read_uint16(d, (uint16_t*) value_ptr);
}

void mff_deserializer_read_int8(mff_deserializer* d, int8_t* value_ptr) {
    mff_deserializer_check_offset(d, 1);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);

    *value_ptr = d->buffer[d->offset++];
}

void mff_deserializer_read_double(mff_deserializer* d, double* value_ptr) {
    mff_deserializer_check_offset(d, 8);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);
    *value_ptr = read_ieee754(&d->buffer[d->offset], 0);
    d->offset += 8;
}

void mff_deserializer_read_float(mff_deserializer* d, float* value_ptr) {
    mff_deserializer_check_offset(d, 4);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);
    *value_ptr = read_ieee754f(&d->buffer[d->offset], 0);
    d->offset += 4;
}

void mff_deserializer_read_buffer(mff_deserializer* d, uint8_t* buffer_ptr, uint32_t length) {
    mff_deserializer_check_offset(d, length);
    MFF_DESERIALIZER_RETURN_ON_FAILURE(d);
    memcpy(buffer_ptr, &d->buffer[d->offset], length);
    d->offset += length;
}
