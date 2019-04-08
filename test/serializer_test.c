#include <mffcodec.h>

#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

void test_serializer_uint32() {
    mff_serializer* s;
    mff_serializer_init(&s);

    mff_serializer_write_uint32(s, 796594737);

    mff_deserializer* d;
    mff_deserializer_init(&d, s->buffer, s->offset);

    uint32_t id;
    mff_deserializer_read_uint32(d, &id);

    assert(id == 796594737);

    mff_serializer_destroy(s);
    mff_deserializer_destroy(d);
}

void test_serializer_float() {
    mff_serializer* s;
    mff_serializer_init(&s);

    mff_serializer_write_float(s, FLT_MIN);
    mff_serializer_write_float(s, FLT_MAX);

    mff_deserializer* d;
    mff_deserializer_init(&d, s->buffer, s->offset);

    float id = 0;

    mff_deserializer_read_float(d, &id);
    assert(mff_deserializer_get_error(d) == MFF_DESERIALIZATION_RESULT_OK);
    assert(id == FLT_MIN);

    mff_deserializer_read_float(d, &id);
    assert(mff_deserializer_get_error(d) == MFF_DESERIALIZATION_RESULT_OK);
    assert(id == FLT_MAX);

    mff_serializer_destroy(s);
    mff_deserializer_destroy(d);
}

void test_serializer_buffer() {
    mff_serializer* s;
    mff_serializer_init(&s);

    const char* string = "test string";
    uint32_t string_length = (uint32_t) strlen(string);
    mff_serializer_write_buffer(s, (uint8_t*) string, string_length);

    mff_deserializer* d;
    mff_deserializer_init(&d, s->buffer, s->offset);

    char output[string_length + 1];
    mff_deserializer_read_buffer(d, (uint8_t*) output, string_length);
    output[string_length] = '\0';

    assert(strcmp(output, "test string") == 0);

    mff_serializer_destroy(s);
    mff_deserializer_destroy(d);
}

void test_serializer_int16() {
    mff_serializer* s;
    mff_serializer_init(&s);

    mff_serializer_write_int16(s, 1000);

    mff_deserializer* d;
    mff_deserializer_init(&d, s->buffer, s->offset);

    int16_t n = 0;
    mff_deserializer_read_int16(d, &n);
    assert(n == 1000);

    mff_serializer_destroy(s);
    mff_deserializer_destroy(d);
}

void test_serializer() {
    test_serializer_uint32();
    test_serializer_float();
    test_serializer_buffer();
    test_serializer_int16();
}
