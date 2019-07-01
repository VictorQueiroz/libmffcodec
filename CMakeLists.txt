cmake_minimum_required(VERSION 3.0)
project(libmffcodec C)

set(CMAKE_C_STANDARD 90)

add_library(mffcodec SHARED src/serializer.c
                            src/deserializer.c
                            src/ieee754.c)
target_include_directories(mffcodec PUBLIC include)
target_link_libraries(mffcodec PRIVATE m)

add_executable(mffcodec_test test/serializer_test.c test/test.c)
target_link_libraries(mffcodec_test PRIVATE mffcodec)
