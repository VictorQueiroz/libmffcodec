#ifndef MFF_IEEE754_H
#define MFF_IEEE754_H

#include <stdint.h>

double read_ieee754(uint8_t *fp, int bigendian);
float read_ieee754f(uint8_t *fp, int bigendian);
void write_ieee754(double x, uint8_t *fp, int bigendian);
void write_ieee754f(float x, uint8_t *fp, int bigendian);

#endif //MFF_IEEE754_H
