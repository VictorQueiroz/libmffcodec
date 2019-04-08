#include "serializer.h"
#include "ieee754.h"

#include <stdlib.h>
#include <string.h>

void mff_serializer_init(mff_serializer** serializer_ptr) {
    *serializer_ptr = calloc(1, sizeof(mff_serializer));

    mff_serializer* s = *serializer_ptr;
    s->length = MFF_SERIALIZER_GROW_SIZE;
    s->error = MFF_SERIALIZATION_RESULT_OK;
    s->buffer = malloc(MFF_SERIALIZER_GROW_SIZE);
}

void mff_serializer_write_int8(mff_serializer* serializer, int8_t value) {
    mff_serializer_adjust_buffer_length(serializer, 1);
    MFF_SERIALIZER_RETURN_ON_FAILURE(serializer);
    serializer->buffer[serializer->offset++] = (uint8_t) value;
}

void mff_serializer_write_uint8(mff_serializer* serializer, uint8_t value) {
    mff_serializer_adjust_buffer_length(serializer, 1);
    MFF_SERIALIZER_RETURN_ON_FAILURE(serializer);
    serializer->buffer[serializer->offset++] = value;
}

void mff_serializer_write_int16(mff_serializer* serializer, int16_t value) {
    mff_serializer_write_uint16(serializer, (uint16_t) value);
}

void mff_serializer_write_uint16(mff_serializer* serializer, uint16_t value) {
    mff_serializer_adjust_buffer_length(serializer, 2);
    MFF_SERIALIZER_RETURN_ON_FAILURE(serializer);

    serializer->buffer[serializer->offset++] = value;
    serializer->buffer[serializer->offset++] = value >> 8;
}

void mff_serializer_write_int32(mff_serializer* serializer, int32_t value) {
    mff_serializer_write_uint32(serializer, (uint32_t) value);
}

void mff_serializer_write_uint32(mff_serializer* serializer, uint32_t value) {
    mff_serializer_adjust_buffer_length(serializer, 4);
    MFF_SERIALIZER_RETURN_ON_FAILURE(serializer);

    uint8_t* buffer = serializer->buffer;

    buffer[serializer->offset++] = value;
    buffer[serializer->offset++] = value >> 8;
    buffer[serializer->offset++] = value >> 16;
    buffer[serializer->offset++] = value >> 24;
}

void mff_serializer_adjust_buffer_length(mff_serializer* serializer, uint32_t length) {
    if((serializer->offset + length) >= serializer->length) {
        serializer->length += (length + MFF_SERIALIZER_GROW_SIZE);
    } else {
        return;
    }
    serializer->buffer = realloc(serializer->buffer, serializer->length);
    if(serializer->buffer == NULL) {
        mff_serializer_set_error_code(serializer, MFF_SERIALIZATION_RESULT_REALLOCATION_FAILED);
    }
}

void mff_serializer_set_error_code(mff_serializer* s, uint8_t error) {
    if(s->error == MFF_SERIALIZATION_RESULT_OK) {
        return;
    }
    s->error = error;
}

void mff_serializer_write_double(mff_serializer* serializer, double value) {
    mff_serializer_adjust_buffer_length(serializer, 8);
    MFF_SERIALIZER_RETURN_ON_FAILURE(serializer);

    write_ieee754(value, &serializer->buffer[serializer->offset], 0);
    serializer->offset += 8;
}

void mff_serializer_write_float(mff_serializer* s, float value) {
    mff_serializer_adjust_buffer_length(s, 4);
    MFF_SERIALIZER_RETURN_ON_FAILURE(s);

    write_ieee754f(value, &s->buffer[s->offset], 0);
    s->offset += 4;
}

void mff_serializer_write_buffer(mff_serializer *s, uint8_t* buffer, uint32_t length) {
    mff_serializer_adjust_buffer_length(s, length);
    MFF_SERIALIZER_RETURN_ON_FAILURE(s);
    memcpy(&s->buffer[s->offset], buffer, length);
    s->offset += length;
}

void mff_serializer_write_string(mff_serializer* s, const char* string) {
    MFF_SERIALIZER_FAIL_IF_NULL(s, string);
    MFF_SERIALIZER_RETURN_ON_FAILURE(s);

    size_t length = strlen(string);
    uint8_t* string_buffer = malloc(length);
    memcpy(string_buffer, string, length);

    mff_serializer_write_buffer(s, string_buffer, length);
    free(string_buffer);
}

void mff_serializer_write_boolean(mff_serializer* s, int value) {
    // TODO: throw error when receive invalid boolean type
    if(value != 0 && value != 1) {
        return;
    }
    mff_serializer_write_uint8(s, value);
}

void mff_serializer_get_data(mff_serializer* s, uint8_t** buffer) {
    *buffer = malloc(s->offset);
    memcpy(*buffer, s->buffer, s->offset);
}

uint8_t mff_serializer_get_error(mff_serializer* s) {
    return s->error;
}

void mff_serializer_destroy(mff_serializer* s) {
    free(s->buffer);
    free(s);
}
