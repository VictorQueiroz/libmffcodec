#include <mffcodec.h>

#include <assert.h>
#include <stdio.h>
#include <float.h>

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

void test_serializer() {
    test_serializer_uint32();
    test_serializer_float();
}
